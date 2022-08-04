## Introduction

### Setup
Download all external libraries with
`./setup.sh`

It downloads [Qt Advanced Docking System](https://github.com/githubuser0xFFFF/Qt-Advanced-Docking-System) in `app/thirdparty`

### Compile Qt Advanced Docking System
1. Follow this [instructions](https://github.com/githubuser0xFFFF/Qt-Advanced-Docking-System#build).
2. Next, copy all generated binary files into the `bin` folder of the IndigoUI project.

### Compile Designer Plugins
Next you have to compile a Qt designer plugin with custom IndigoUI Widgets.

1. Open `indigouiwidgets.pro` file and compile the library
2. Move the generated *.so file to Qt Designer Plugin folder. Find your Qt installation folder and add your plugin to:
`Qt/Tools/QtCreator/lib/Qt/plugins/designer`

### Configure Scribus-IndigoUI Project
1. Open Scribus-IndigoUI.pro file in Qt Creator
2. Go to `Projects->Run` in Qt Creator and configure the output path of the binary. It should be the `bin` folder.
3. Set folder to: `Scribus-IndigoUI/build-debug/../bin`
4. Click on Run button (Ctrl + R) and compile the project.

