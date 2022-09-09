/***************************************************************************
 *   Copyright (C) 2005-2015 by the Quassel Project                        *
 *   devel@quassel-irc.org                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) version 3.                                           *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 *                                                                         *
 * *************************************************************************
     This is a modified version of original code on:
     https://github.com/quassel/quassel/blob/master/src/uisupport/qssparser.h
 */

#ifndef THEME_MANAGER_H
#define THEME_MANAGER_H


#include <QString>
#include <QStyle>
#include <QPalette>
#include <QHash>


class ThemeManager :public QObject
{

    Q_OBJECT


public:
    ThemeManager(ThemeManager const&) = delete;
    void operator=(ThemeManager const&) = delete;
    static ThemeManager& instance();


    inline QPalette palette() const { return m_palette; }

    void setup();
    void parseTheme(QString &styleString);

    QString themeName();
    QString styleSheet();

    QColor parseColor(const QString str);

    bool isDark();


protected:
    QHash<QString, QPalette::ColorRole> _paletteColorRoles;
    QHash<QString, QPalette::ColorGroup> _paletteColorGroups;

 private:

    ThemeManager(QObject *parent = nullptr);
    ~ThemeManager() = default;

    static ThemeManager* m_instance;

    QString m_theme;
    QPalette m_palette;
    QString m_styleSheet;

    void builtPalette(QString group, QString role, QString color);
    void debugColorPalette(QString key, QPalette::ColorRole role);

signals:

public slots:
};

#endif // THEME_MANAGER_H
