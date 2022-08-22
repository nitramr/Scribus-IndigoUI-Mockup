#ifndef UTIL_FILE_H
#define UTIL_FILE_H

#include <QIcon>
#include <QString>
#include <QPalette>



class UtilFile
{
public:
    UtilFile();

    // File
    static QString readFile(QString filePath);
    static QIcon mimeIconFromFile(QString filePath);




};

#endif // UTIL_FILE_H
