/***************************************************************************
    copyright            : (C) 2015 by Craig Bradney
    email                : mrb@scribus.info
***************************************************************************/

/***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/
#ifndef ICON_MANAGER_H
#define ICON_MANAGER_H

#include <QDomElement>
#include <QIcon>
#include <QObject>
#include "pixmapcache.h"
#include "structs.h"



class IconManager: public QObject
{

    Q_OBJECT



public:
    IconManager(IconManager const&) = delete;
    void operator=(IconManager const&) = delete;
    static IconManager& instance();

    void setIconsForDarkMode(bool forDarkMode);
    QColor baseColor();

    void clearCache();
    void rebuildCache();
    bool createCache();

    bool setup(bool forDarkMode = false);

    QCursor cursor(const QString& name, int hotX = -1, int hotY = -1);
    QIcon icon(const QString& name);
    QPixmap pixmap(const QString& name);

    void addIcon(const QString & name, QPainterPath path);

protected:
    const QString classDark = "onDark";
    const QString tagIcon = "icon";
    const QString colorOnDark = "onDark";
    const QString colorOnLight = "onLight";

private:

    IconManager(QObject *parent = nullptr);
    ~IconManager() = default;

    static IconManager* m_instance;

    QMap<QString, IconSetData> m_iconSets;
    QMap<QString, QPainterPath*> m_iconPaths;
    PixmapCache<QString> m_pxCache;
    QString m_activeSetBasename;
    QString m_activeSetVersion;
    QString m_backupSetBasename;
    QString m_backupSetVersion;
    bool m_forDarkMode;

    bool initIconSets();
    void readIconConfigFiles();

    QPixmap *loadPixmap(const QString filePath, QColor color);
    QPixmap *renderPath(QPainterPath path);
    void renderIcons();

    bool readXMLFile(QString filePath, QDomDocument &document, QString fileExtenstion);
//    void tintPixmap(QPixmap &pixmap, QColor color);

    void applyColors(QDomDocument &doc, QString fileName, QColor color);
    QMap<QString, QString> * parseStyleSheet(QString styleString);



};

#endif // ICON_MANAGER_H
