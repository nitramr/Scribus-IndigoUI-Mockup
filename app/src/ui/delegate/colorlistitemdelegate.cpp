#include "colorlistitemdelegate.h"

#include "colorpixmapvalue.h"
#include "iconmanager.h"
#include "helper.h"

/* ********************************************************************************* *
 *
 * Fancy Item
 *
 * ********************************************************************************* */

void ColorFancyItemDelegate::redraw(const QVariant& data) const
{
    static QPixmap smallPix(16, 16);

    QPixmap* pPixmap = ScListBoxPixmap<70, 16>::pmap.data();
    pPixmap->fill(Qt::transparent);

    if (data.canConvert<ColorPixmapValue>())
    {
        ColorPixmapValue item(data.value<ColorPixmapValue>());



        //QColor rgb = ScColorEngine::getDisplayColor(item.m_color, item.m_doc);
        QColor rgb = item.m_color.toQColor();
        smallPix.fill(rgb);
        QPainter painter(&smallPix);
        painter.setBrush(Qt::NoBrush);
        QPen b(qApp->palette().midlight().color(), 1);
        painter.setPen(b);
        painter.drawRect(0, 0, 15, 15);
        painter.end();

        Helper::paintIcon(smallPix, *pPixmap, 0, 0);

        if (item.m_color.isOutOfGamut())
            Helper::paintIcon(alertIcon.scaled(QSize(16,16), Qt::KeepAspectRatio, Qt::SmoothTransformation), *pPixmap, 18, 0);


        switch(item.m_color.getColorModel()){
        case ColorModel::CMYK:
            Helper::paintIcon(cmykIcon.scaled(QSize(16,16), Qt::KeepAspectRatio, Qt::SmoothTransformation), *pPixmap, 36, 0);
            break;
        case ColorModel::HSV:
        case ColorModel::RGB:
            Helper::paintIcon(rgbIcon.scaled(QSize(16,16), Qt::KeepAspectRatio, Qt::SmoothTransformation), *pPixmap, 36, 0);
            break;
        case ColorModel::Lab:
            Helper::paintIcon(labIcon.scaled(QSize(16,16), Qt::KeepAspectRatio, Qt::SmoothTransformation), *pPixmap, 36, 0);
            break;

        }


        if (item.m_color.isSpotColor()){
            Helper::paintIcon(spotIcon.scaled(QSize(16,16), Qt::KeepAspectRatio, Qt::SmoothTransformation), *pPixmap, 54, 0);
        }


        if (item.m_color.isRegistrationColor()){
            Helper::paintIcon(regIcon.scaled(QSize(16,16), Qt::KeepAspectRatio, Qt::SmoothTransformation), *pPixmap, 54, 0);
        }
    }
}

QString ColorFancyItemDelegate::text(const QVariant& data) const
{
    if (data.canConvert<ColorPixmapValue>())
        return data.value<ColorPixmapValue>().m_name;
    return data.toString();
}

void ColorFancyItemDelegate::iconSetChange()
{
    IconManager& iconManager = IconManager::instance();

    alertIcon = iconManager.pixmap("color-alert");
    cmykIcon = iconManager.pixmap("color-cmyk");
    rgbIcon = iconManager.pixmap("color-rgb");
    labIcon = iconManager.pixmap("color-lab");
    spotIcon = iconManager.pixmap("color-spot");
    regIcon = iconManager.pixmap("color-register");
}

/* ********************************************************************************* *
 *
 * Small Item
 *
 * ********************************************************************************* */

void ColorSmallItemDelegate::redraw(const QVariant& data) const
{
    QPixmap* pPixmap = ScListBoxPixmap<16, 16>::pmap.data();
    pPixmap->fill(Qt::transparent);
    if (data.canConvert<ColorPixmapValue>())
    {
        ColorPixmapValue item(data.value<ColorPixmapValue>());
        //QColor rgb = ScColorEngine::getDisplayColor(item.m_color, item.m_doc);
        QColor rgb = item.m_color.toQColor();
        pPixmap->fill(rgb);
        QPainter painter(pPixmap);
        painter.setBrush(Qt::NoBrush);
        QPen b(qApp->palette().midlight().color(), 1);
        painter.setPen(b);
        painter.drawRect(0, 0, 15, 15);
        painter.end();
    }
}

QString ColorSmallItemDelegate::text(const QVariant& data) const
{
    if (data.canConvert<ColorPixmapValue>())
        return data.value<ColorPixmapValue>().m_name;
    return data.toString();
}

/* ********************************************************************************* *
 *
 * Wide item
 *
 * ********************************************************************************* */

void ColorWideItemDelegate::redraw(const QVariant& data) const
{
    QPixmap* pPixmap = ScListBoxPixmap<32, 16>::pmap.data();
    pPixmap->fill(Qt::transparent);
    if (data.canConvert<ColorPixmapValue>())
    {
        ColorPixmapValue item(data.value<ColorPixmapValue>());
        //QColor rgb = ScColorEngine::getDisplayColor(item.m_color, item.m_doc);
        QColor rgb = item.m_color.toQColor();
        pPixmap->fill(rgb);
    }
}


QString ColorWideItemDelegate::text(const QVariant& data) const
{
    if (data.canConvert<ColorPixmapValue>())
        return data.value<ColorPixmapValue>().m_name;
    return data.toString();
}
