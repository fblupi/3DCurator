cmake_minimum_required(VERSION 3.1.0)

if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()

if(POLICY CMP0043)
  cmake_policy(SET CMP0043 NEW)
endif()

set(LANGUAGE "en")

set(APP_NAME "3DCurator")
set(APP_VERSION "0.2-beta")

if (APPLE)
  set(APP_ICON ${CMAKE_CURRENT_SOURCE_DIR}/../assets/icons/3DCurator.icns)
else()
  set(APP_ICON ${CMAKE_CURRENT_SOURCE_DIR}/../assets/icons/3DCurator.rc)
endif()

set(CMAKE_CONFIGURATION_TYPES Release)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

PROJECT(3DCurator)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})
if(ITKVtkGlue_LOADED)
  find_package(VTK REQUIRED)
  include(${VTK_USE_FILE})
else()
  find_package(ItkVtkGlue REQUIRED)
  include(${ItkVtkGlue_USE_FILE})
  set(GLUE ItkVtkGlue)
endif()

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)
find_package(Qt5Core REQUIRED QUIET)
find_package(Qt5Gui REQUIRED QUIET)
find_package(Qt5LinguistTools REQUIRED QUIET)
find_package(Qt5Widgets REQUIRED QUIET)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${Boost_INCLUDE_DIRS})

file(GLOB_RECURSE HEADER_FILES *.h)
file(GLOB_RECURSE CPP_FILES *.cpp)
file(GLOB_RECURSE UI_FILES *.ui)
file(GLOB_RECURSE QRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../assets/*.qrc)

add_executable(${APP_NAME} WIN32 MACOSX_BUNDLE ${APP_ICON} ${UI_FILES} ${QRC_FILES} ${HEADER_FILES} ${CPP_FILES})
target_link_libraries(${APP_NAME} Qt5::Core Qt5::Gui Qt5::Widgets ${GLUE} ${VTK_LIBRARIES} ${ITK_LIBRARIES} ${OpenCV_LIBS} ${Boost_LIBS})

if(APPLE)
  set(MACOSX_BUNDLE_ICON_FILE 3DCurator.icns)
  if(LANGUAGE STREQUAL "es")
    set(MACOSX_BUNDLE_INFO_STRING "Visor 3D de TC de esculturas de madera policromada") 
  else()
    set(MACOSX_BUNDLE_INFO_STRING "3D Viewer for CTs of Polychromed Wood Sculptures")
  endif()
  set_target_properties(${APP_NAME}
    PROPERTIES
      MACOSX_BUNDLE_BUNDLE_NAME "${APP_NAME} ${APP_VERSION}"
      MACOSX_BUNDLE_BUNDLE_VERSION ${APP_VERSION}
      MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/MacOSXBundleInfo.plist.in
    )
  set_source_files_properties(${APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
endif()
