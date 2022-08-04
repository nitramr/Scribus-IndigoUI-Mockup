QTDIR_build {
# This is only for the Qt build. Do not use externally. We mean it.
PLUGIN_TYPE = designer
PLUGIN_CLASS_NAME = IndigoUIWidgets
load(qt_plugin)
CONFIG += install_ok
} else {
# Public example:

TEMPLATE = lib
CONFIG  += plugin

TARGET   = $$qtLibraryTarget($$TARGET)

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

}

QT      += widgets designer


# import widgets from main project
include ($$PWD/../thirdparty/Qt-Color-Widgets/color_widgets.pri)

HEADERS += \
    $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/color_preview_plugin.hpp \
    $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/color_wheel_plugin.hpp \
    $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/color_widget_plugin_collection.hpp \
    $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/gradient_slider_plugin.hpp \
    $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/hue_slider_plugin.hpp \
    $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/color_selector_plugin.hpp \
    $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/color_list_plugin.hpp \
    $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/swatch_plugin.hpp \
    $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/color_palette_widget_plugin.hpp \
    $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/color_2d_slider_plugin.hpp \
    $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/color_line_edit_plugin.hpp \
    $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/gradient_editor_plugin.hpp

SOURCES += \
  $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/color_preview_plugin.cpp \
  $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/color_wheel_plugin.cpp \
  $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/color_widget_plugin_collection.cpp \
  $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/gradient_slider_plugin.cpp \
  $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/hue_slider_plugin.cpp \
  $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/color_selector_plugin.cpp \
  $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/color_list_plugin.cpp \
  $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/swatch_plugin.cpp \
  $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/color_palette_widget_plugin.cpp \
  $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/color_2d_slider_plugin.cpp \
  $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/color_line_edit_plugin.cpp \
  $$PWD/../thirdparty/Qt-Color-Widgets/color_widgets_designer_plugin/gradient_editor_plugin.cpp
