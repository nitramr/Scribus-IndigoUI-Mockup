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
include ($$PWD/../src/ui/widgets/widgets.pri)

HEADERS += \
    indigoui/basepointwidgetplugin.h \
    indigoui/formwidgetplugin.h \
    indigoui/headlinewidgetplugin.h \
    indigoui/indigoui.h \
    indigoui/sectioncontainerextension.h \
    indigoui/sectioncontainerextensionfactory.h \
    indigoui/sectioncontainerplugin.h

SOURCES += \
    indigoui/basepointwidgetplugin.cpp \
    indigoui/formwidgetplugin.cpp \
    indigoui/headlinewidgetplugin.cpp \
    indigoui/indigoui.cpp \
    indigoui/sectioncontainerextension.cpp \
    indigoui/sectioncontainerextensionfactory.cpp \
    indigoui/sectioncontainerplugin.cpp
