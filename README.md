# 3DCurator

> Francisco Javier Bolívar Lupiáñez

## Descripción

Software para visualizar e interactuar con los datos DICOM de esculturas.

## Software utilizado

* CMake 3.7.2
* Visual Studio Community 2017
* Qt5.9.1
* VTK 8.0.0
* ITK 4.12.0
* Boost 1.64.0
* OpenCV 3.2.0

## Instalación y configuración

### Windows

#### Entorno de desarrollo

##### Visual Studio Community 2017

* Descargar Visual Studio Community 2017 desde su [web oficial](https://www.visualstudio.com/es-es/downloads/download-visual-studio-vs.aspx) e instalar.

##### Qt5.9.1

* Descargar Qt5.9.1 desde [este enlace](http://download.qt.io/official_releases/qt/5.9/5.9.1/qt-opensource-windows-x86-5.9.1.exe) de su web e instalar para `msvc2017 64-bit`.
* Crear una nueva variable de entorno con nombre: `QTDIR` y valor: `C:\Qt\Qt5.9.1` (directorio raiz de la versión instalada).
* Agregar al Path la siguiente dirección: `C:\Qt\Qt5.9.1\5.9.1\msvc2017_64\bin`

##### CMake 3.8.2

* Descargar CMake 3.8.2 desde [este enlace](https://cmake.org/files/v3.8/cmake-3.8.2-win64-x64.msi) de su web e instalar (al instalar recomiendo marcar la opción de agregar al PATH de todos los usuarios para no tener que hacerlo manualmente).

#### Construir librerías

##### Estructura de directorios

Recomiendo usar la siguiente estructura de directorios:

```
C:\
  |-- librería\
  |   |-- versión1\
  |   |   |-- src\
  |   |   |-- build\
  |   |       |-- compilador1
  |   |       |-- compilador2
  |   |
  |   |-- versión2\
  |       |-- src\
  |       |-- build\
  |           |-- compilador1
  |
  |-- librería\
  |   |-- versión\
  |       |-- src\
  |       |-- build\
  |           |-- compilador1
  |-- ...
```

De esta forma es más fácil organizar versiones para una u otra plataforma de distintas versiones de la librería.

##### VTK 8.0.0

* Descargar VTK 8.0.0 desde [este enlace](http://www.vtk.org/files/release/8.0/VTK-8.0.0.zip) de su web oficial.
* Abrir CMake y completar:
  + src: `C:\VTK\8.0.0\src`
  + build: `C:\VTK\8.0.0\build\msvc2017_64`
* Elegir como generador `Visual Studio 15 2017 Win64`.
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
  + `QT_QMAKE_EXECUTABLE:PATHFILE=C:/Qt/Qt5.9.1/5.9.1/msvc2017_64/bin/qmake.exe`
  + `CMAKE_PREFIX_PATH:PATH=C:/Qt/Qt5.9.1/5.9.1/msvc2017_64/`
* Presionar en configurar y aparecerá un error, habrá que elegir como versión de Qt la 5. Elegirla y volver a configurar.
* Configurar hasta que no aparezca ningún campo en rojo.
* Una vez configurado todo, pulsar en generar. Esto creará una serie de archivos en `C:\VTK\8.0.0\build\msvc2017_64`.

##### ITK 4.12.0

* Descargar ITK 4.12.0 desde [este enlace](https://sourceforge.net/projects/itk/files/itk/4.11/InsightToolkit-4.12.0.zip/download) de su web oficial.
* Abrir CMake y completar:
  + src: `C:\ITK\4.12.0\src`
  + build: `C:\ITK\4.12.0\build\msvc2017_64`
* Elegir como generador `Visual Studio 15 2017 Win64`.
* Presionar en configurar.
* Una vez haya generado seleccionar el siguiente campo:
  + `Module_ITKVtkGlue`
* Configurar y aparecerá un error de que no encuentra `VTK_DIR`. Darle valor de `C:\VTK\8.0.0\build\msvc2017_64`.
* Configurar hasta que no aparezca ningún campo en rojo.
* Una vez configurado todo, pulsar en generar. Esto creará una serie de archivos en `C:\ITK\4.12.0\build\msvc2017_64`.

#### Compilar librerías

##### VTK 8.0.0

* Abrir `VTK.sln`.
* Construir `ALL_BUILD` en modo *Release* y esperar unos minutos a que termine (en mi caso tardó unos 30 minutos).
* Copiar los archivos `QVTKWidgetPlugin.lib` y `QVTKWidgetPlugin.dll` que se encuentran en `C:\VTK\8.0.0\build\msvc2017_64\lib\Release` y  `C:\VTK\8.0.0\build\msvc2017_64\bin\Release` respectivamente en `C:\Qt\Qt5.9.1\5.9.1\msvc2017_64\plugins\designer` (Si no se encuentran los archivos, comprobar que en CMake se marcó la opción `BUILD_SHARED_LIBS`). Esto hará que desde Qt Designer se pueda crea un `QVTKWidget`.
* Crear una nueva variable de entorno con nombre: `VTK_DIR` y valor: `C:\VTK\8.0.0\build\msvc2017_64`.
* Agregar al Path la siguiente dirección: `%VTK_DIR%\bin\Release`.

##### ITK 4.12.0

* Abrir `ITK.sln`.
* Construir `ALL_BUILD` en modo *Release* y esperar unos minutos a que termine (en mi caso tardó unos 30 minutos).
* Crear una nueva variable de entorno con nombre: `ITK_DIR` y valor: `C:\ITK\4.12.0\build\msvc2017_64`.
* Agregar al Path la siguiente dirección: `%ITK_DIR%\bin\Release`.

##### Boost 1.64.0

* Descargar Boost 1.64.0 desde [este enlace](http://sourceforge.net/projects/boost/files/boost/1.64.0/) de su web oficial.
* Descomprimir en cualquier lugar, abrir la consola de comandos de Visual Studio y moverse al lugar donde ha sido extraído.
* Escribir `bootstrap.bat` para generar el *Boost.Build*.
* Compilar con: `b2 toolset=msvc --build-type=complete --abbreviate-paths address-model=64 install -j4`.
* Crear una nueva variable de entorno con nombre: `BOOST_ROOT` y valor: `C:\Boost`.

##### OpenCV 3.2.0

* Descargar OpenCV desde [este enlace](https://sourceforge.net/projects/opencvlibrary/files/opencv-win/3.2.0/opencv-3.2.0-vc14.exe/download).
* Ejecutar y extraer.
* Mover el directorio extraído a `C:\OpenCV\3.2.0\`.
* Crear una nueva variable de entorno con nombre: `OPENCV_ROOT` y valor: `C:\OpenCV\3.2.0\opencv\build\x64\vc14\`.
* Crear una nueva variable de entorno con nombre: `OPENCV_DIR` y valor: `%OPENCV_ROOT%\lib`.
* Agregar al Path la siguiente dirección: `%OPENCV_ROOT%\bin`.

#### Configurar proyecto

Una vez generado el proyecto con CMake realizar los siguientes cambios en la configuración:

* En *Project Properties* ir a *Configuration Properties > Linker > System* y:
  + En *SubSystem* seleccionar la opción *Windows (/SUBSYSTEM:WINDOWS)*.
  + En *Enable Large Adresses* seleccionar la opción *Yes (/LARGEADRESSAWARE)*.

#### Lanzar ejecutable generado

Una vez compilado, antes de ejecutar, mover al directorio donde se ha generado el ejecutable (carpeta `Release`) los siguientes archivos DLL que se encuentran en `C:\Qt\Qt5.9.1\5.9.1\msvc2017_64\bin`:

* `libEGL.dll`
* `libGLESv2.dll`
* `Qt5Core.dll`
* `Qt5Gui.dll`
* `Qt5Widgets.dll`

Si no se hace, es posible que salte un mensaje de error parecido al siguiente: 

```
The procedure entry point ?rgbSwapped@QImage@@QEHAA$$QEAV1@Z could not be located in the dynamic link library C:\VTK\8.0.0\build\bin\Release\vtkGUISupportQt-8.0.dll
```

### Linux

En construcción...
