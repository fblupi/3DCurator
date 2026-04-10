#!/bin/bash
set -e

# Configuration
APP_NAME="3DCurator"
BUILD_DIR="build"
APP_BUNDLE="$BUILD_DIR/$APP_NAME.app"
LIBS_DIR="$APP_BUNDLE/Contents/libs"
EXECUTABLE="$APP_BUNDLE/Contents/MacOS/$APP_NAME"

echo "=== Bundling $APP_NAME.app ==="

# Check the app exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: $EXECUTABLE not found. Run 'make' in $BUILD_DIR first."
    exit 1
fi

# Step 1: Deploy Qt frameworks
echo ""
echo "[1/6] Deploying Qt frameworks..."
macdeployqt "$APP_BUNDLE" -verbose=0 2>/dev/null || true
echo "  Done."

# Step 2: Bundle all non-system dylibs
echo ""
echo "[2/6] Bundling dynamic libraries..."
mkdir -p "$LIBS_DIR"
dylibbundler -od -b \
    -x "$EXECUTABLE" \
    -d "$LIBS_DIR" \
    -p @executable_path/../libs/ \
    -s /opt/homebrew/lib
echo "  Done."

# Step 3: Also fix libs inside Qt plugins and frameworks
echo ""
echo "[3/6] Fixing Qt plugin dependencies..."
find "$APP_BUNDLE/Contents/PlugIns" -name "*.dylib" 2>/dev/null | while read plugin; do
    echo "  Fixing: $(basename "$plugin")"
    dylibbundler -of -b \
        -x "$plugin" \
        -d "$LIBS_DIR" \
        -p @executable_path/../libs/ \
        -s /opt/homebrew/lib 2>/dev/null || true
done
echo "  Done."

# Step 4: Fix all rpaths and install names in Frameworks
echo ""
echo "[4/6] Fixing rpaths and install names in Frameworks..."
for lib in "$APP_BUNDLE/Contents/Frameworks"/*.dylib; do
    chmod +w "$lib" 2>/dev/null

    # Fix install name (ID) if it points to an absolute path
    id=$(otool -D "$lib" 2>/dev/null | tail -1)
    if echo "$id" | grep -q "/opt/homebrew\|/usr/local"; then
        install_name_tool -id "@rpath/$(basename "$lib")" "$lib" 2>/dev/null || true
    fi

    # Fix references to absolute Homebrew paths
    otool -L "$lib" 2>/dev/null | awk '{print $1}' | grep "/opt/homebrew\|/usr/local" | while read dep; do
        base=$(basename "$dep")
        if [ -f "$APP_BUNDLE/Contents/Frameworks/$base" ]; then
            install_name_tool -change "$dep" "@rpath/$base" "$lib" 2>/dev/null || true
        fi
    done

    # Delete all non-@loader_path rpaths and ensure @loader_path exists
    otool -l "$lib" 2>/dev/null | grep -A2 "LC_RPATH" | grep "path " | sed 's/.*path //' | sed 's/ (offset.*//' | while read rp; do
        if [ "$rp" != "@loader_path" ]; then
            install_name_tool -delete_rpath "$rp" "$lib" 2>/dev/null || true
        fi
    done
    if ! otool -l "$lib" 2>/dev/null | grep -A2 "LC_RPATH" | grep -q "@loader_path"; then
        install_name_tool -add_rpath "@loader_path" "$lib" 2>/dev/null || true
    fi
done
echo "  Done."

# Step 5: Verify no external references remain
echo ""
echo "[5/6] Checking for remaining external references..."
ISSUES=0
for f in "$EXECUTABLE" "$LIBS_DIR"/*.dylib; do
    BAD=$(otool -L "$f" 2>/dev/null | grep -v "@executable_path" | grep -v "@rpath" | grep -v "@loader_path" | grep -v "/usr/lib" | grep -v "/System" | grep -v ":" | grep -v "self" || true)
    if [ -n "$BAD" ]; then
        echo "  WARNING: $(basename "$f") still references:"
        echo "$BAD"
        ISSUES=$((ISSUES + 1))
    fi
done
if [ "$ISSUES" -eq 0 ]; then
    echo "  All clear - no external references found."
else
    echo "  $ISSUES file(s) have external references (may still work if they're optional)."
fi

# Step 6: Code sign (ad-hoc) so macOS doesn't block it
echo ""
echo "[6/6] Code signing..."
codesign --force --deep --sign - "$APP_BUNDLE" 2>/dev/null
echo "  Done."

# Summary
echo ""
echo "=== Bundle complete ==="
SIZE=$(du -sh "$APP_BUNDLE" | cut -f1)
echo "  App: $APP_BUNDLE ($SIZE)"
echo ""
echo "To distribute, zip it:"
echo "  cd $BUILD_DIR && zip -r $APP_NAME.zip $APP_NAME.app"
