#ifndef SHORTCUTMANAGER_H
#define SHORTCUTMANAGER_H

#include <QObject>
#include <QDomDocument>
#include <QMap>

class ShortcutManager : public QObject
{

    Q_OBJECT
public:

    ShortcutManager(ShortcutManager const&) = delete;
    void operator=(ShortcutManager const&) = delete;
    static ShortcutManager& instance();

    void setup();

    QStringList keySets();
    QKeySequence keySequence(QString name);

private:

    ShortcutManager(QObject *parent = nullptr);
    ~ShortcutManager() = default;

    static ShortcutManager* m_instance;

    QMap<QString, QString> keyMap;
    QMap<QString, QString> keySetList;
    QStringList m_keySets;

    bool loadKeySetFile();
    void importKeySet(const QString&filename);

    bool readXMLFile(QString filePath, QDomDocument &document);

    QStringList readKeysetConfigFiles();
};

#endif // SHORTCUTMANAGER_H
