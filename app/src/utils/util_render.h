#ifndef UTILRENDER_H
#define UTILRENDER_H

#include <QPainter>

class UtilRender
{
public:
    UtilRender();

    static void renderPattern(QPainter *painter, QRectF rect);
    static void renderCircularHandle(QPainter * painter, QPointF center, qreal width, QBrush background);
    static void renderPointerHandle(QPainter * painter, QPointF pointer, qreal width, QColor background);
    static QPixmap renderSplitColor(QSize size, QColor color, Qt::Orientations orientation = Qt::Horizontal, qreal mid = 0.5);
    static void paintIcon(const QPixmap &toPaint, QPixmap &target, int x = 0, int y = 0);
};

#endif // UTILRENDER_H
