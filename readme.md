## IndigoUI
## What is IndigoUI?
IndigoUI is an experimental UI framework for Scribus. The primary focus is to adapt the Scribus user interface and experience to the needs of modern desktop publishing software. 

## Installation & Compilation

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

### Preview

![Bildschirmfoto vom 2022-08-04 19-59-02](https://user-images.githubusercontent.com/15112256/182931586-db6be82c-30d7-4a81-9f44-2fa1cba91d8b.png)
