#ifndef HELPER_H
#define HELPER_H

#include <QIcon>
#include <QString>
#include <QPalette>
#include <QtMath>


#define DegToRad(x) ((x) * M_PI / 180)
#define RadToDeg(x) ((x) / M_PI * 180)


class Helper
{
public:
    Helper();

    // File
    static QString readFile(QString filePath);
    static QIcon mimeIconFromFile(QString filePath);

    // Graphic
    static void renderPattern(QPainter *painter, QRectF rect);
    static void renderColorHandle(QPainter * painter, QPointF center, qreal radius, QBrush background);
    static QPixmap renderSplitColor(QSize size, QColor color);
    static void paintIcon(const QPixmap &toPaint, QPixmap &target, int x = 0, int y = 0);


};

#endif // HELPER_H
