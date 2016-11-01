# 3DCurator

> Francisco Javier Bolívar Lupiáñez

## Descripción

Software para visualizar e interactuar con los datos DICOM de esculturas.

## Software utilizado

* CMake 3.4.1
* Visual Studio Community 2015
* Qt5.7.0
* VTK 7.0.0
* ITK 4.10.1
* Boost 1.61.0

## Instalación y configuración

### Windows

#### Entorno de desarrollo

##### Visual Studio Community 2015

* Descargar Visual Studio Community 2015 desde su [web oficial](https://www.visualstudio.com/es-es/downloads/download-visual-studio-vs.aspx) e instalar.

##### Qt5.7.0

* Descargar Qt5.7.0 desde [este enlace](http://download.qt.io/official_releases/qt/5.7/5.7.0/qt-opensource-windows-x86-msvc2015-5.7.0.exe) de su web e instalar.
* Crear una nueva variable de entorno con nombre: `QTDIR` y valor: `C:\Qt\Qt5.7.0` (directorio raiz de la versión instalada).
* Agregar al Path la siguiente dirección: `C:\Qt\Qt5.7.0\5.7\msvc2015\bin`

##### CMake 3.6.1

* Descargar CMake 3.6.1 desde [este enlace](https://cmake.org/files/v3.6/cmake-3.6.1-win64-x64.msi) de su web e instalar (al instalar recomiendo marcar la opción de agregar al PATH de todos los usuarios para no tener que hacerlo manualmente).

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

##### VTK 7.0.0

* Descargar VTK 7.0.0 desde [este enlace](http://www.vtk.org/files/release/7.0/VTK-7.0.0.zip) de su web oficial.
* Abrir CMake y completar:
  + src: `C:\VTK\7.0.0\src`
  + build: `C:\VTK\7.0.0\build`
* Elegir como generador `Visual Studio 14 2015`.
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
  + `QT_QMAKE_EXECUTABLE:PATHFILE=C:/Qt/Qt5.7.0/5.7/msvc2015/bin/qmake.exe`
  + `CMAKE_PREFIX_PATH:PATH=C:/Qt/Qt5.7.0/5.7/msvc2015/`
* Presionar en configurar y aparecerá un error, habrá que elegir como versión de Qt la 5. Elegirla y volver a configurar.
* Configurar hasta que no aparezca ningún campo en rojo.
* Una vez configurado todo, pulsar en generar. Esto creará una serie de archivos en `C:\VTK\7.0.0\build`.

##### ITK 4.10.1

* Descargar ITK 4.10.1 desde [este enlace](https://sourceforge.net/projects/itk/files/itk/4.10/InsightToolkit-4.10.1.zip/download) de su web oficial.
* Abrir CMake y completar:
  + src: `C:\ITK\4.10.1\src`
  + build: `C:\ITK\4.10.1\build`
* Elegir como generador `Visual Studio 14 2015`.
* Presionar en configurar.
* Una vez haya generado seleccionar el siguiente campo:
  + `Module_ITKVtkGlue`
* Configurar y aparecerá un error de que no encuentra `VTK_DIR`. Darle valor de `C:\VTK\7.0.0\build`.
* Configurar hasta que no aparezca ningún campo en rojo.
* Una vez configurado todo, pulsar en generar. Esto creará una serie de archivos en `C:\ITK\4.10.1\build`.

#### Compilar librerías

##### VTK 7.0.0

* Abrir `VTK.sln`.
* Construir `ALL_BUILD` en modo *Release* y esperar unos minutos a que termine (en mi caso tardó unos 20 minutos).
* Construir `INSTALL` en modoe *Release*.
* Copiar los archivos `QVTKWidgetPlugin.lib` y `QVTKWidgetPlugin.dll` que se encuentran en `C:\VTK\7.0.0\build\lib\Release` y  `C:\VTK\7.0.0\build\bin\Release` respectivamente en `C:\Qt\Qt5.7.0\5.7\msvc2015\plugins\designer` (Si no se encuentran los archivos, comprobar que en CMake se marcó la opción `BUILD_SHARED_LIBS`) . Esto hará que desde Qt Designer se pueda crea un `QVTKWidget`.´
* Crear una nueva variable de entorno con nombre: `VTK_DIR` y valor: `C:\VTK\7.0.0\build`.
* Agregar al Path la siguiente dirección: `%VTK_DIR%\bin\Release`

##### ITK 4.10.1

* Abrir `ITK.sln`.
* Construir en modo *Release* y esperar unos minutos a que termine (en mi caso tardó unos 20 minutos).
* Crear una nueva variable de entorno con nombre: `ITK_DIR` y valor: `C:\ITK\4.10.1\build`.
* Agregar al Path la siguiente dirección: `%ITK_DIR%\bin\Release`

##### Boost 1.61.0

* Descargar Boost 1.61.0 desde [este enlace](http://sourceforge.net/projects/boost/files/boost/1.61.0/) de su web oficial.
* Descomprimir en cualquier lugar, abrir la consola de comandos de Visual Studio y moverse al lugar donde ha sido extraído.
* Escribir `bootstrap.bat` para generar el Boost.Build.
* Compilar con: `b2 toolset=msvc --build-type=complete --abbreviate-paths address-model=64 install -j4`.
* Agregar al proyecto de Visual Studio:
  + En *Project Properties* ir a *Configuration Properties > C/C++ > General > Additional Include Directories* y añadir el directorio `C:\Boost\include\boost-1_61`.
  + En *Project Properties* ir a *Configuration Properties > Linker > Additional Library Directories* y añadir el directorio `C:\Boost\lib`.

#### Configurar proyecto

Una vez generado el proyecto con CMake realizar los siguientes cambios en la configuración:

* En *Project Properties* ir a *Configuration Properties > Linker > System* y:
  + En *SubSystem* seleccionar la opción *Windows (/SUBSYSTEM:WINDOWS)*.
  + En *Enable Large Adresses* seleccionar la opción *Yes (/LARGEADRESSAWARE)*.

### Linux

En construcción...