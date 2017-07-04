# 3DCurator

> Francisco Javier Bolívar Lupiáñez

## Description

A 3D Viewer for CTs of Polychromed Wood Sculptures. Further info in [https://fblupi.github.io/3DCurator/](https://fblupi.github.io/3DCurator/).

## License

[GNU General Public License Version 3](LICENSE).

![GNU GPL v3](https://camo.githubusercontent.com/cffb10a3e84f202bdac9c38fe1f9c212a7a8b59a/68747470733a2f2f646c2e64726f70626f7875736572636f6e74656e742e636f6d2f732f7430796c76697337663173746375372f47504c2d332e302e706e67)

## Software

* CMake 3.7.2
* Visual Studio Community 2017
* Qt5.9.1
* VTK 8.0.0
* ITK 4.12.0
* Boost 1.64.0
* OpenCV 3.2.0

## Installation and configuration for developers

### Windows

#### Development environment

##### Visual Studio Community 2017

* Download [Visual Studio Community 2017](https://www.visualstudio.com/es-es/downloads/download-visual-studio-vs.aspx) and install.

##### Qt5.9.1

* Download [Qt5.9.1](http://download.qt.io/official_releases/qt/5.9/5.9.1/qt-opensource-windows-x86-5.9.1.exe) and install for `msvc2017 64-bit`.
* Create a new environment variable `QTDIR` with the value `C:\Qt\Qt5.9.1`.
* Add to the path: `C:\Qt\Qt5.9.1\5.9.1\msvc2017_64\bin`.

##### CMake 3.8.2

* Download [CMake 3.8.2](https://cmake.org/files/v3.8/cmake-3.8.2-win64-x64.msi) and install.

#### Build libraries

##### Directories structure

I strongly recommend to use the directories structure below:

```
C:\
  |-- library1\
  |   |-- version1\
  |   |   |-- src\
  |   |   |-- build\
  |   |       |-- compiler1
  |   |       |-- compiler2
  |   |
  |   |-- version2\
  |       |-- src\
  |       |-- build\
  |           |-- compiler1
  |
  |-- library2\
  |   |-- version1\
  |       |-- src\
  |       |-- build\
  |           |-- compiler1
  |-- ...
```

Thus it will be easier to migrate from one version to another.

##### VTK 8.0.0

* Download [VTK 8.0.0](http://www.vtk.org/files/release/8.0/VTK-8.0.0.zip) and extract files.
* Open CMake and complete the fields:
  + src: `C:\VTK\8.0.0\src`
  + build: `C:\VTK\8.0.0\build\msvc2017_64`
* Use `Visual Studio 15 2017 Win64` as generator.
* Press configure.
* Check advanced options.
* Once generated choose these options:
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
* Add two new entries:
  + `QT_QMAKE_EXECUTABLE:PATHFILE=C:/Qt/Qt5.9.1/5.9.1/msvc2017_64/bin/qmake.exe`
  + `CMAKE_PREFIX_PATH:PATH=C:/Qt/Qt5.9.1/5.9.1/msvc2017_64/`
* Press configure and an error will appear, you have to change the Qt version to the 5 and configure again.
* Configure until there is no red option.
* Then press generate. It will create some files and folders in `C:\VTK\8.0.0\build\msvc2017_64`.

##### ITK 4.12.0

* Download [ITK 4.12.0](https://sourceforge.net/projects/itk/files/itk/4.11/InsightToolkit-4.12.0.zip/download) and extract files.
* Open CMake and complete the fields:
  + src: `C:\ITK\4.12.0\src`
  + build: `C:\ITK\4.12.0\build\msvc2017_64`
* Use `Visual Studio 15 2017 Win64` as generator.
* Press configure.
* Check advanced options.
* Once configured check this option:
  + `Module_ITKVtkGlue`
* Press configure and an error will appear. Give `VTK_DIR` this path `C:\VTK\8.0.0\build\msvc2017_64`.
* Configure until there is no red option.
* Then press generate. It will create some files and folders in `C:\ITK\4.12.0\build\msvc2017_64`.

#### Compile libraries

##### VTK 8.0.0

* Open `VTK.sln`.
* Build `ALL_BUILD` in *Release* mode and wait for a long time until it finish.
* Copy the files `QVTKWidgetPlugin.lib` and `QVTKWidgetPlugin.dll` stored in `C:\VTK\8.0.0\build\msvc2017_64\lib\Release` and `C:\VTK\8.0.0\build\msvc2017_64\bin\Release` respectively and paste in `C:\Qt\Qt5.9.1\5.9.1\msvc2017_64\plugins\designer`. We will be able to use `QVTKWidget` in QtDesigner doing this.
* Create a new environment variable `VTK_DIR` with the value `C:\VTK\8.0.0\build\msvc2017_64`.
* Add to the path: `%VTK_DIR%\bin\Release`.

##### ITK 4.12.0

* Open `ITK.sln`.
* Build `ALL_BUILD` in *Release* mode and wait for a long time until it finish.
* Create a new environment variable `ITK_DIR` with the value `C:\ITK\4.12.0\build\msvc2017_64`.
* Add to the path: `%ITK_DIR%\bin\Release`.

##### Boost 1.64.0

* Download [Boost 1.64.0](http://sourceforge.net/projects/boost/files/boost/1.64.0/) de su web oficial.
* Extract and open Development Command Prompt for VS2017 in the folder where we have extracted the files.
* Type `bootstrap.bat` to generate *Boost.Build*.
* Compile with: `b2 toolset=msvc --build-type=complete --abbreviate-paths address-model=64 install -j4`.
* Create a new environment variable `BOOST_ROOT` with the value `C:\Boost`.

##### OpenCV 3.2.0

* Download [OpenCV 3.2.0](https://sourceforge.net/projects/opencvlibrary/files/opencv-win/3.2.0/opencv-3.2.0-vc14.exe/download).
* Execute and extract.
* Move the extracted directory to `C:\OpenCV\3.2.0\`.
* Create a new environment variable `OPENCV_ROOT` with the value `C:\OpenCV\3.2.0\opencv\build\x64\vc14\`.
* Create a new environment variable `OPENCV_DIR` with the value `%OPENCV_ROOT%\lib`.
* Add to the path: `%OPENCV_ROOT%\bin`.

#### Configure project

Once 3DCurator project is generated open *Project Properties* go to *Configuration Properties > Linker > System* and:
* In *SubSystem* select the option *Windows (/SUBSYSTEM:WINDOWS)*.
* In *Enable Large Adresses* select the option *Yes (/LARGEADRESSAWARE)*.

#### Execute program

If you get this error when you execute the program: 

```
The procedure entry point ?rgbSwapped@QImage@@QEHAA$$QEAV1@Z could not be located in the dynamic link library C:\VTK\8.0.0\build\bin\Release\vtkGUISupportQt-8.0.dll
```

Copy to the `Release` folder the DLL files below (you can find them in `C:\Qt\Qt5.9.1\5.9.1\msvc2017_64\bin`):

* `libEGL.dll`
* `libGLESv2.dll`
* `Qt5Core.dll`
* `Qt5Gui.dll`
* `Qt5Widgets.dll`

### Linux

Building...