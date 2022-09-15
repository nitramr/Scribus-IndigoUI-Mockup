#include "configuration_manager.h"

#include <QCoreApplication>
#include "dirpaths_manager.h"

ConfigurationManager::ConfigurationManager()
{

}


QString ConfigurationManager::files(QString fileName)
{
    QMap<QString, QString> *list = new QMap<QString, QString>();
    list->insert("app_layout", DirPathsManager::instance().settingsDir() + "layout_settings.ini");
    list->insert("app_default_theme", DirPathsManager::instance().themeDir() + "scribus_dark.qss");


    return list->value(fileName, "");

}

