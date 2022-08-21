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

#include "helper.h"

#include <QDir>
#include <QFile>
#include <QMimeDatabase>
#include "iconmanager.h"
#include "qpainter.h"

/* ********************************************************************************* *
 *
 * Constructor
 *
 * ********************************************************************************* */

Helper::Helper(){}

/* ********************************************************************************* *
 *
 * File
 *
 * ********************************************************************************* */

QString Helper::readFile(QString filePath)
{
    QFile file( filePath );
    file.open( QFile::ReadOnly );

    return QString( file.readAll() );
}

QIcon Helper::mimeIconFromFile(QString filePath)
{
    QMimeDatabase mime_database;
    const QString nativeName = QDir::toNativeSeparators(filePath);

    QList<QMimeType> mime_types = mime_database.mimeTypesForFileName(nativeName);
    QIcon icon = QIcon::fromTheme(mime_types[0].iconName());

    // if meme can't find load fallback icon
    if (icon.isNull()) icon = IconManager::instance().icon("file-outline");

    return icon;
}

/* ********************************************************************************* *
 *
 * Graphic
 *
 * ********************************************************************************* */

void Helper::renderPattern(QPainter *painter, QRectF rect)
{
    QImage pattern(rect.width(), rect.height(), QImage::Format_ARGB32_Premultiplied);

    QPainter p(&pattern);
    p.fillRect(pattern.rect(), QBrush(Qt::white));

    int cellSize = 4;
    int cellSizeX = rect.width() / cellSize + cellSize;
    int cellSizeY = rect.height() / cellSize + cellSize;

    for(int y = 0; y < cellSizeY; y++)
        for(int x = y % 2; x < cellSizeX; x+=2)
            p.fillRect(QRectF(x * cellSize, y * cellSize, cellSize, cellSize), QBrush(Qt::lightGray));

    painter->drawImage(rect, pattern);
}


void Helper::renderCircularHandle(QPainter *painter, QPointF center, qreal width, QBrush background)
{
    qreal radius = width /2.;

    painter->save();

    // Draw background
    painter->setBrush(background);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(center, radius, radius);

    painter->setBrush(Qt::NoBrush);

    // Draw white ring
    painter->setPen(QPen(Qt::white, 2));
    painter->drawEllipse(center, radius-1, radius-1);

    // Draw black ring
    painter->setPen(QPen(Qt::black, 1));
    painter->drawEllipse(center, radius, radius);

    painter->restore();
}

void Helper::renderPointerHandle(QPainter *painter, QPointF pointer, qreal width, QColor background)
{

    qreal height = width *1.5;
    QRect rect( pointer.x() -width/2, pointer.y() , width, height );

    QPainterPath path;
    path.moveTo(pointer);
    path.lineTo(pointer + QPoint(width/2, height/3) );
    path.lineTo(pointer + QPoint(width/2, height) );
    path.lineTo(pointer + QPoint(-width/2, height) );
    path.lineTo(pointer + QPoint(-width/2, height/3) );
    path.closeSubpath();

    painter->save();

    // Draw white border
    painter->setPen(QPen(Qt::black, 3));
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path);

    // Draw background
    painter->setClipPath(path);
    painter->setPen(Qt::NoPen);
    renderPattern(painter, rect);

    // Draw color
    painter->drawPixmap(rect, renderSplitColor(rect.size(), background, Qt::Vertical, 0.7) );

    // Draw black border
    painter->setBrush(Qt::NoBrush);
    painter->setClipping(false);
    painter->setPen(QPen(Qt::white, 1.5));
    painter->drawPath(path);

    painter->restore();

}

QPixmap Helper::renderSplitColor(QSize size, QColor color, Qt::Orientations orientation, qreal mid)
{
    mid = qBound(0., mid, 1.);

    QPixmap pixmap(size.width(), size.height());
    pixmap.fill(Qt::transparent);

    QRectF solid( 0, 0, pixmap.width()*mid, pixmap.height() );
    QRectF alpha( pixmap.width()*mid, 0, pixmap.width()*(1-mid), pixmap.height() );

    if(orientation == Qt::Vertical){
        solid = QRectF(0, 0, pixmap.width(), pixmap.height() *mid);
        alpha = QRectF(0, pixmap.height() *mid, pixmap.width(), pixmap.height() * (1-mid) );
    }

    QColor col = color;
    col.setAlphaF(1);

    QPainter p(&pixmap);
    p.setBrush(QBrush(col));
    p.setPen(Qt::NoPen);
    p.drawRect(solid);
    p.setBrush(QBrush(color));
    p.drawRect(alpha);

    return pixmap;
}


void Helper::paintIcon(const QPixmap &toPaint, QPixmap &target, int x, int y)
{
    QPainter p;
    p.begin(&target);
    p.drawPixmap(x, y, toPaint);
    p.end();
}
