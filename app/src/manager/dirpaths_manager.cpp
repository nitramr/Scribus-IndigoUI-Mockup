/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#include "dirpaths_manager.h"

#include <QDir>
#include <QCoreApplication>

#if defined(Q_OS_WIN32) || defined (Q_OS_OS2)
const char DirPathsManager::envPathSeparator = ';';
const char DirPathsManager::pathSeparator = '\';
#else
const char DirPathsManager::envPathSeparator = ':';
const char DirPathsManager::pathSeparator = '/';
#endif


DirPathsManager* DirPathsManager::m_instance = nullptr;


const DirPathsManager& DirPathsManager::instance()
{
    if (!DirPathsManager::m_instance)
        DirPathsManager::m_instance = new DirPathsManager();
    return *DirPathsManager::m_instance;
}


void DirPathsManager::destroy()
{
    delete DirPathsManager::m_instance;
}


DirPathsManager::DirPathsManager()
{

}

DirPathsManager::~DirPathsManager() = default;



const QString  DirPathsManager::iconDir() const
{
    return directory(Directory::Icon);
}

const QString DirPathsManager::appDir() const
{
    return directory(Directory::App);
}

const QString DirPathsManager::settingsDir() const
{
    return directory(Directory::Settings);
}

const QString DirPathsManager::themeDir() const
{
    return directory(Directory::Theme);
}

const QString DirPathsManager::keysetsDir() const
{
    return directory(Directory::Keysets);
}


const QString DirPathsManager::directory(Directory name) const
{
    QString appPath =  QCoreApplication::applicationDirPath();
    QString dir = "";

    switch(name){
    case Directory::App:
        dir = appPath;
        break;
    case Directory::Icon:
        dir = appPath + pathSeparator + "iconsets";
        break;
    case Directory::Settings:
        dir = appPath;
        break;
    case Directory::Theme:
        dir = appPath + pathSeparator + "themes";
        break;
    case Directory::Keysets:
        dir = appPath + pathSeparator + "keysets";
        break;
    }

   return dir + pathSeparator;
}
