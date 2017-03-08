# 3DCurator

> Francisco Javier Bolívar Lupiáñez

## Descripción

Software para visualizar e interactuar con los datos DICOM de esculturas.

## Software utilizado

* CMake 3.7.2
* Visual Studio Community 2015
* Qt5.7.0
* VTK 7.1.0
* ITK 4.11.0
* Boost 1.63.0

## Instalación y configuración

### Windows

#### Entorno de desarrollo

##### Visual Studio Community 2015

* Descargar Visual Studio Community 2015 desde su [web oficial](https://www.visualstudio.com/es-es/downloads/download-visual-studio-vs.aspx) e instalar.

##### Qt5.8.0

* Descargar Qt5.7.0 desde [este enlace](http://download.qt.io/official_releases/qt/5.8/5.8.0/qt-opensource-windows-x86-msvc2015_64-5.8.0.exe) de su web e instalar.
* Crear una nueva variable de entorno con nombre: `QTDIR` y valor: `C:\Qt\Qt5.8.0` (directorio raiz de la versión instalada).
* Agregar al Path la siguiente dirección: `C:\Qt\Qt5.8.0\5.8\msvc2015_64\bin`

##### CMake 3.7.2

* Descargar CMake 3.7.2 desde [este enlace](https://cmake.org/files/v3.7/cmake-3.7.2-win64-x64.msi) de su web e instalar (al instalar recomiendo marcar la opción de agregar al PATH de todos los usuarios para no tener que hacerlo manualmente).

#### Construir librerías

##### Estructura de directorios

Recomiendo usar la siguiente estructura de directorios:

```
C:\
  |-- librería\
  |   |-- versión1\
  |   |   |-- src\
  |   |   |-- build\
  |   |
  |   |-- versión2\
  |       |-- src\
  |       |-- build\
  |
  |-- librería\
  |   |-- versión\
  |       |-- src\
  |       |-- build\
  |-- ...
```

De esta forma es más fácil organizar versiones para una u otra plataforma de distintas versiones de la librería.

##### VTK 7.1.0

* Descargar VTK 7.1.0 desde [este enlace](http://www.vtk.org/files/release/7.1/VTK-7.1.0.zip) de su web oficial.
* Abrir CMake y completar:
  + src: `C:\VTK\7.1.0\src`
  + build: `C:\VTK\7.1.0\build`
* Elegir como generador `Visual Studio 14 2015 Win64`.
* Presionar en configurar.
* Una vez haya generado seleccionar los siguientes campos:
  + `BUILD_SHARED_LIBS`
  + `Module_vtkDICOM`
  + `Module_vtkGUISupportQt`
  + `Module_vtkGUISupportQtOpenGL`
  + `Module_vtkGUISupportQtSQL`
  + `Module_vtkGUISupportQtWebkit`
  + `Module_vtkRenderingQt`
  + `Module_vtkViewsQt`
  + `VTK_Group_Imaging`
  + `VTK_Group_Qt`
* Agregar dos entradas:
  + `QT_QMAKE_EXECUTABLE:PATHFILE=C:/Qt/Qt5.8.0/5.8/msvc2015_64/bin/qmake.exe`
  + `CMAKE_PREFIX_PATH:PATH=C:/Qt/Qt5.8.0/5.8/msvc2015_64/`
* Presionar en configurar y aparecerá un error, habrá que elegir como versión de Qt la 5. Elegirla y volver a configurar.
* Configurar hasta que no aparezca ningún campo en rojo.
* Una vez configurado todo, pulsar en generar. Esto creará una serie de archivos en `C:\VTK\7.1.0\build`.

##### ITK 4.11.0

* Descargar ITK 4.11.0 desde [este enlace](https://sourceforge.net/projects/itk/files/itk/4.11/InsightToolkit-4.11.0.zip/download) de su web oficial.
* Abrir CMake y completar:
  + src: `C:\ITK\4.11.0\src`
  + build: `C:\ITK\4.11.0\build`
* Elegir como generador `Visual Studio 14 2015 Win64`.
* Presionar en configurar.
* Una vez haya generado seleccionar el siguiente campo:
  + `Module_ITKVtkGlue`
* Configurar y aparecerá un error de que no encuentra `VTK_DIR`. Darle valor de `C:\VTK\7.1.0\build`.
* Configurar hasta que no aparezca ningún campo en rojo.
* Una vez configurado todo, pulsar en generar. Esto creará una serie de archivos en `C:\ITK\4.11.0\build`.

#### Compilar librerías

##### VTK 7.1.0

* Abrir `VTK.sln`.
* Construir `ALL_BUILD` en modo *Release* y esperar unos minutos a que termine (en mi caso tardó unos 30 minutos).
* Copiar los archivos `QVTKWidgetPlugin.lib` y `QVTKWidgetPlugin.dll` que se encuentran en `C:\VTK\7.1.0\build\lib\Release` y  `C:\VTK\7.0.0\build\bin\Release` respectivamente en `C:\Qt\Qt5.8.0\5.8\msvc2015_64\plugins\designer` (Si no se encuentran los archivos, comprobar que en CMake se marcó la opción `BUILD_SHARED_LIBS`) . Esto hará que desde Qt Designer se pueda crea un `QVTKWidget`.´
* Crear una nueva variable de entorno con nombre: `VTK_DIR` y valor: `C:\VTK\7.1.0\build`.
* Agregar al Path la siguiente dirección: `%VTK_DIR%\bin\Release`

##### ITK 4.11.0

* Abrir `ITK.sln`.
* Construir `ALL_BUILD` en modo *Release* y esperar unos minutos a que termine (en mi caso tardó unos 30 minutos).
* Crear una nueva variable de entorno con nombre: `ITK_DIR` y valor: `C:\ITK\4.11.0\build`.
* Agregar al Path la siguiente dirección: `%ITK_DIR%\bin\Release`

##### Boost 1.63.0

* Descargar Boost 1.63.0 desde [este enlace](http://sourceforge.net/projects/boost/files/boost/1.63.0/) de su web oficial.
* Descomprimir en cualquier lugar, abrir la consola de comandos de Visual Studio y moverse al lugar donde ha sido extraído.
* Escribir `bootstrap.bat` para generar el Boost.Build.
* Compilar con: `b2 toolset=msvc --build-type=complete --abbreviate-paths address-model=64 install -j4`.
* Agregar al proyecto de Visual Studio:
  + En *Project Properties* ir a *Configuration Properties > C/C++ > General > Additional Include Directories* y añadir el directorio `C:\Boost\include\boost-1_63`.
  + En *Project Properties* ir a *Configuration Properties > Linker > Additional Library Directories* y añadir el directorio `C:\Boost\lib`.

#### Configurar proyecto

Una vez generado el proyecto con CMake realizar los siguientes cambios en la configuración:

* En *Project Properties* ir a *Configuration Properties > Linker > System* y:
  + En *SubSystem* seleccionar la opción *Windows (/SUBSYSTEM:WINDOWS)*.
  + En *Enable Large Adresses* seleccionar la opción *Yes (/LARGEADRESSAWARE)*.

#### Lanzar ejecutable generado

Una vez compilado, antes de ejecutar, mover al directorio donde se ha generado el ejecutable (carpeta `Release`) los siguientes archivos DLL que se encuentran en `C:\Qt\Qt5.8.0\5.8\msvc2015_64\bin`:

* libEGL.dll
* libGLESv2.dll
* Qt5Core.dll
* Qt5Gui.dll
* Qt5Widgets.dll

Si no se hace, es posible que salte un mensaje de error parecido al siguiete: *The procedure entry point ?rgbSwapped@QImage@@QEHAA$$QEAV1@Z could not be located in the dynamic link library C:\VTK\7.1.0\build\bin\Release\vtkGUISupportQt-7.1.dll*.

### Linux

En construcción...
