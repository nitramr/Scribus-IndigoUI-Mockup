/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#ifndef DIRPATHS_MANAGER_H
#define DIRPATHS_MANAGER_H

#include <QString>
#include <QStringList>

class DirPathsManager
{
public:

    typedef enum {App, Icon, Settings, Theme} Directory;

        /**
         * @brief Get a reference to the ScPaths instance
         *        creating it if necessary.
         * @sa ScPaths::destroy()
         */
        static const DirPathsManager& instance();
        /**
         * @brief Destroy the DirPathsManager instance, if any.
         * @sa ScPaths::instance()
         */
        static void destroy();

        /*** The separator used between path list entries in environment variables */
        static const char envPathSeparator;
        static const char pathSeparator;

        const QString directory(Directory name) const;

        /** @brief Return path to icons directory*/
        const QString iconDir() const;

        /** @brief Return path to app directory*/
        const QString appDir() const;

        /** @brief Return path to settings directory*/
        const QString settingsDir() const;

        /** @brief Return path to theme directory*/
        const QString themeDir() const;


    protected:
        /** @brief Constructor. Use DirPathsManager::instance() instead. */
        DirPathsManager();
        /** @brief Destructor. Use DirPathsManager::destroy() instead. */
        ~DirPathsManager();

        /** @brief Pointer to existing instance of DirPathsManager, if any. */
        static DirPathsManager* m_instance;


};

#endif // DIRPATHS_MANAGER_H
