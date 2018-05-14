# 3DCurator

> Francisco Javier Bolívar Lupiáñez

![3DCurator icon](https://fblupi.github.io/3DCurator/img/icon.png)

## Description

A 3D Viewer for CTs of Polychromed Wood Sculptures. Further info in [https://fblupi.github.io/3DCurator/](https://fblupi.github.io/3DCurator/)

## License

[GNU General Public License Version 3](LICENSE)

![GNU GPL v3](https://camo.githubusercontent.com/cffb10a3e84f202bdac9c38fe1f9c212a7a8b59a/68747470733a2f2f646c2e64726f70626f7875736572636f6e74656e742e636f6d2f732f7430796c76697337663173746375372f47504c2d332e302e706e67)

## Software

* CMake 3.11.1 (2018, April)
* Visual Studio Community 2017 15.7.1 (2018, May)
* Qt5.10.1 (2018, Feb)
* VTK 8.1.1 (2018, May)
* ITK 4.13.0 (2017, Dec)
* Boost 1.67.0 (2018, Apr)
* OpenCV 3.4.1 (2018, Feb)

## Installation and configuration for developers

### Windows

#### Development environment

##### Visual Studio Community 2017

* Download [Visual Studio Community 2017](https://www.visualstudio.com/es-es/downloads/download-visual-studio-vs.aspx) and install

##### Qt5.10.1

* Download [Qt5.10.1](http://download.qt.io/official_releases/qt/5.10/5.10.1/qt-opensource-windows-x86-5.10.1.exe) and install for `msvc2017 64-bit`
* Create a new environment variable `QTDIR` with the value `C:\Qt\Qt5.10.1`
* Add to the path: `C:\Qt\Qt5.10.1\5.10.1\msvc2017_64\bin`

##### CMake 3.11.1

* Download [CMake 3.11.1](https://cmake.org/files/v3.11/cmake-3.11.1-win64-x64.msi) and install

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

Thus it will be easier to migrate from one version to another

##### VTK 8.1.1

* Download [VTK 8.1.1](http://www.vtk.org/files/release/8.1/VTK-8.1.1.zip) and extract files
* Open CMake and complete the fields:
  + src: `C:\VTK\8.1.1\src`
  + build: `C:\VTK\8.1.1\build\msvc2017_64`
* Use `Visual Studio 15 2017 Win64` as generator
* Press configure
* Check advanced options
* Once generated check these options:
  + `Module_vtkDICOM`
  + `Module_vtkGUISupportQt`
  + `Module_vtkGUISupportQtOpenGL`
  + `Module_vtkRenderingQt`
  + `Module_vtkViewsQt`
  + `VTK_Group_Imaging`
  + `VTK_Group_Qt`
* Press configure and an error will appear, you have to change the Qt version to the 5 and configure again
* Configure until there is no red option
* Then press generate. It will create some files and folders in `C:\VTK\8.1.1\build\msvc2017_64`

##### ITK 4.13.0

* Download [ITK 4.13.0](https://sourceforge.net/projects/itk/files/itk/4.13/InsightToolkit-4.13.0.zip/download) and extract files
* Open CMake and complete the fields:
  + src: `C:\ITK\4.13.0\src`
  + build: `C:\ITK\4.13.0\build\msvc2017_64`
* Use `Visual Studio 15 2017 Win64` as generator
* Press configure
* Check advanced options
* Once configured check this option:
  + `Module_ITKVtkGlue`
* Press configure and an error will appear. Give `VTK_DIR` this path `C:\VTK\8.1.1\build\msvc2017_64`
* Configure until there is no red option
* Then press generate. It will create some files and folders in `C:\ITK\4.13.0\build\msvc2017_64`

#### Compile libraries

##### VTK 8.1.1

* Open `VTK.sln`
* Build `ALL_BUILD` in *Release* mode and wait for a long time until it finish
* Create a new environment variable `VTK_DIR` with the value `C:\VTK\8.1.1\build\msvc2017_64`
* Add to the path: `%VTK_DIR%\bin\Release`

##### ITK 4.13.0

* Open `ITK.sln`
* Build `ALL_BUILD` in *Release* mode and wait for a long time until it finish
* Create a new environment variable `ITK_DIR` with the value `C:\ITK\4.13.0\build\msvc2017_64`
* Add to the path: `%ITK_DIR%\bin\Release`

##### Boost 1.67.0

* Download [Boost 1.67.0](http://sourceforge.net/projects/boost/files/boost/1.67.0/) de su web oficial
* Extract and open Development Command Prompt for VS2017 in the folder where we have extracted the files
* Type `bootstrap.bat` to generate *Boost.Build*
* Compile with: `b2 toolset=msvc --build-type=complete --abbreviate-paths address-model=64 install -j4`
* Create a new environment variable `BOOST_ROOT` with the value `C:\Boost`

##### OpenCV 3.4.1

* Download [OpenCV 3.4.1](https://sourceforge.net/projects/opencvlibrary/files/opencv-win/3.4.1/opencv-3.4.1-vc14_vc15.exe/download)
* Execute and extract
* Move the extracted directory to `C:\OpenCV\3.4.1\`
* Create a new environment variable `OPENCV_ROOT` with the value `C:\OpenCV\3.4.1\opencv\build\x64\vc15\`
* Create a new environment variable `OPENCV_DIR` with the value `%OPENCV_ROOT%\lib`
* Add to the path: `%OPENCV_ROOT%\bin`

#### Project Build

* Open CMake and complete the fields:
  + src: `%PROJECT_PATH%\src`
  + build: `%PROJECT_PATH%\build`
* Use `Visual Studio 15 2017 Win64` as generator
* Configure until there is no red option
* Then press generate. It will create some files and folders in `%PROJECT_PATH%\build`
* Open `3DCurator.sln`
* Open *Project Properties* go to *Configuration Properties > Linker > System* and:
  * In *SubSystem* select the option *Windows (/SUBSYSTEM:WINDOWS)*
  * In *Enable Large Adresses* select the option *Yes (/LARGEADRESSAWARE)*
* Set `3DCurator` solution as default project
* Once compiled, copy to the `build\Release` folder the DLL files `libEGL.dll`, `libGLESv2.dll`, `Qt5Core.dll`, `Qt5Gui.dll` and `Qt5Widgets.dll` from `C:\Qt\Qt5.10.1\5.10.1\msvc2017_64\bin` and `qwindows.dll` from `C:\Qt\Qt5.10.1\5.10.1\msvc2017_64\plugins\platforms`

### Linux

Building...

### Mac OS X

Building...