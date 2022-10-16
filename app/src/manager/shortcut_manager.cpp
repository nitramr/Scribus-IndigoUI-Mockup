#include "shortcut_manager.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDomElement>
#include <QKeySequence>

#include "configuration_manager.h"
#include "dirpaths_manager.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

ShortcutManager* ShortcutManager::m_instance = nullptr;

ShortcutManager::ShortcutManager(QObject *parent)
    : QObject(parent)
{

    keyMap = QMap<QString, QString>();
    keySetList = QMap<QString, QString>();

}

ShortcutManager& ShortcutManager::instance()
{
    static ShortcutManager m_instance;
    return m_instance;
}

void ShortcutManager::setup()
{
    m_keySets = readKeysetConfigFiles();

//    // load first keyset
//    if(keySetList.size() > 0 && m_keySets.size() > 0){
//        importKeySet(keySetList[m_keySets.at(0)] );
//    }

    importKeySet( ConfigurationManager::files("app_default_keyset") );

}

/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

QStringList ShortcutManager::keySets()
{
    return m_keySets;
}

QKeySequence ShortcutManager::keySequence(QString name)
{
    if (keyMap.contains(name))
        return QKeySequence(keyMap.value(name));

    return QKeySequence();
}

/* ********************************************************************************* *
 *
 * Private Member
 *
 * ********************************************************************************* */

QStringList ShortcutManager::readKeysetConfigFiles()
{
    keySetList.clear();
    QString location(DirPathsManager::instance().keysetsDir());
    QDir keySetsDir(QDir::toNativeSeparators(location), "*.xml", QDir::Name, QDir::Files | QDir::NoSymLinks);
    if ((!keySetsDir.exists()) || (keySetsDir.count() <= 0))
        return QStringList();

    QStringList appNames;
    for (uint fileCounter = 0; fileCounter < keySetsDir.count(); ++fileCounter)
    {
        QString filename(QDir::toNativeSeparators(location+keySetsDir[fileCounter]));
        QDomDocument doc("keymapentries");

        if(!readXMLFile(filename, doc)) continue;

        QDomElement docElem = doc.documentElement();
        if (docElem.tagName() == "shortcutset" && docElem.hasAttribute("name"))
        {
            QDomAttr nameAttr = docElem.attributeNode("name");
            //                if(nameAttr.value().contains(ScribusAPI::getVersionScribus().remove(".svn")))
            //                    appNames.prepend(nameAttr.value());
            //                else
            appNames.append(nameAttr.value());
            keySetList.insert(nameAttr.value(), filename);
        }
    }
    return QStringList(appNames);
}

/* ********************************************************************************* *
 *
 * Private Methods
 *
 * ********************************************************************************* */

void ShortcutManager::importKeySet(const QString &filename)
{
    QFileInfo fi(filename);
    if (!fi.exists())
        return;

    //import the file into qdomdoc
    QDomDocument doc( "keymapentries" );

    if(!readXMLFile(filename, doc)) return;

    //load the file now
    QDomElement docElem = doc.documentElement();
    if (docElem.tagName() == "shortcutset" && docElem.hasAttribute("name"))
    {
        QDomAttr keysetAttr = docElem.attributeNode( "name" );

//        //clear current menu entries
//        for (QMap<QString, QString>::Iterator it = keyMap.begin(); it != keyMap.end(); ++it){
//            it.value() = "";
//        }

        keyMap.clear();

        //load in new set
        for (QDomNode n = docElem.firstChild(); !n.isNull(); n = n.nextSibling())
        {
            QDomElement e = n.toElement();
            if (e.isNull())
                continue;
            if (e.hasAttribute("name") && e.hasAttribute("shortcut"))
            {
                QDomAttr nameAttr = e.attributeNode("name");
                QDomAttr shortcutAttr = e.attributeNode("shortcut");
                if (keyMap.contains(nameAttr.value()))
                    keyMap[nameAttr.value()] = shortcutAttr.value();
                else
                    keyMap.insert(nameAttr.value(), shortcutAttr.value());
            }
        }
    }

}

bool ShortcutManager::readXMLFile(QString filePath, QDomDocument &document)
{
    QFile file1( filePath );
    if ( !file1.open( QIODevice::ReadOnly ) )
        return false;
    QTextStream ts(&file1);
    ts.setEncoding(QStringConverter::Utf8);
    QString errorMsg;
    int eline;
    int ecol;
    if ( !document.setContent( ts.readAll(), &errorMsg, &eline, &ecol ))
    {
        qDebug("%s", QString("Could not open key set file: %1\nError:%2 at line: %3, row: %4").arg(filePath, errorMsg).arg(eline).arg(ecol).toLatin1().constData());
        file1.close();
        return false;
    }
    file1.close();

    return true;
}
