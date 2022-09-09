#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <QIcon>
#include <QString>
#include <QPalette>



class FileUtils
{
public:
    FileUtils();

    // File
    static QString readFile(QString filePath);
    static QIcon mimeIconFromFile(QString filePath);




};

#endif // FILE_UTILS_H
