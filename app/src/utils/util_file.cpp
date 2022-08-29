/*
MIT License

Copyright (c) 2017 Berendea Nicolae

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "util_file.h"

#include <QDir>
#include <QFile>
#include <QMimeDatabase>
#include "iconmanager.h"


/* ********************************************************************************* *
 *
 * Constructor
 *
 * ********************************************************************************* */

UtilFile::UtilFile(){}

/* ********************************************************************************* *
 *
 * File
 *
 * ********************************************************************************* */

QString UtilFile::readFile(QString filePath)
{
    QFile file( filePath );
    file.open( QFile::ReadOnly );

    return QString( file.readAll() );
}

QIcon UtilFile::mimeIconFromFile(QString filePath)
{
    QMimeDatabase mime_database;
    const QString nativeName = QDir::toNativeSeparators(filePath);

    QList<QMimeType> mime_types = mime_database.mimeTypesForFileName(nativeName);
    QIcon icon = QIcon::fromTheme(mime_types[0].iconName());

    // if meme can't find load fallback icon
    if (icon.isNull()) icon = IconManager::instance().icon("file-outline");

    return icon;
}



