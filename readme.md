# IndigoUI
## What is IndigoUI?
IndigoUI is an experimental UI framework for Scribus. The primary focus is to adapt the Scribus user interface and experience to the needs of modern desktop publishing software.

## Project
This project does not claim to be full software. It is a test balloon of the user interface that can be tested for both usability and technical runnability.

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
3. Set folder to: `Scribus-IndigoUI-Mockup/build-debug/../bin`
4. Click on Run button (Ctrl + R) and compile the project.

### Preview

![Bildschirmfoto vom 2022-08-04 19-59-02](https://user-images.githubusercontent.com/15112256/182931586-db6be82c-30d7-4a81-9f44-2fa1cba91d8b.png)

## Features
1. UI theme support for dark and light themes
2. Dynamic icon sets (support of SVG files with inline and CSS included styles; automatic color adjustment based on ui theme)
3. Functional color picker and gradient editor
4. Custom layout widgets available as Qt Designer plugins
5. Custom widgets:
  * new base point widget support rotation of selected item
  * new arrange pages widget support page previews and page orientation

### Themes

|![Bildschirmfoto vom 2022-09-15 19-10-07](https://user-images.githubusercontent.com/15112256/190467927-40cac002-91ca-4902-9588-1cb0a796b302.png)|![Bildschirmfoto vom 2022-09-15 19-10-30](https://user-images.githubusercontent.com/15112256/190467980-dd1fcafc-4d21-427b-9b77-dc2d40c2b318.png)|![Bildschirmfoto vom 2022-09-15 19-09-04](https://user-images.githubusercontent.com/15112256/190468026-64a601a7-afea-4bb7-b30b-98226f434e5e.png)|![Bildschirmfoto vom 2022-09-15 19-09-42](https://user-images.githubusercontent.com/15112256/190468060-26a4ba69-004b-4a29-91f2-3018a90bd179.png)|
|---|---|---|---|
|Lighter|Light|Dark|Darker|

Currently, there is no in-built option to switch the theme. To switch the theme you have to change it in `config_manager.cpp`
```c++
list->insert("app_default_theme", DirPathsManager::instance().themeDir() + "scribus_light.qss");
```

### Widget Gallery
#### Color Button
![Bildschirmfoto vom 2022-08-07 18-55-25](https://user-images.githubusercontent.com/15112256/190470547-1c3bed91-486a-412c-8298-ac272321f531.png)
![Bildschirmfoto vom 2022-08-07 18-56-09](https://user-images.githubusercontent.com/15112256/190470559-a55ac6ab-69f7-4ce3-b097-7b50969e58b4.png)

#### Color Slider
![Bildschirmfoto vom 2022-09-15 19-20-58](https://user-images.githubusercontent.com/15112256/190470691-55098218-60b2-4150-b7a3-a74763a1311e.png)

#### Gradient Edit

![Bildschirmfoto vom 2022-09-15 19-22-27](https://user-images.githubusercontent.com/15112256/190470652-d7f2605b-67e2-4b8b-9b91-b895979865dd.png)

#### Color Harmony Wheel
![Bildschirmfoto vom 2022-09-15 19-20-28](https://user-images.githubusercontent.com/15112256/190470758-d4b7be8a-fd1f-42ff-99d4-678a4fb41af1.png)

#### Page Arrange Widget
![Bildschirmfoto vom 2022-09-15 19-23-10](https://user-images.githubusercontent.com/15112256/190470889-058146c6-6fbd-48eb-b216-400d18996b24.png)
