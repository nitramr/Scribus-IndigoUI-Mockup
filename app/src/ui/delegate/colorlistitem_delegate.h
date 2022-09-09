#ifndef COLORLISTITEM_DELEGATE_H
#define COLORLISTITEM_DELEGATE_H

#include <memory>

#include <QAbstractItemDelegate>
#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QScopedPointer>
#include <QStyleOptionViewItem>
#include <QVariant>

class QVariant;

/* ********************************************************************************* *
 *
 * ListBoxPixmap
 *
 * ********************************************************************************* */

template<unsigned int pixWidth, unsigned int pixHeight>
class ScListBoxPixmap : public QAbstractItemDelegate
{
public:
    ScListBoxPixmap(void);

    virtual QString text(const QVariant&) const = 0;

    // Functions reimplemented from QAbstractItemDelegate
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const override;
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const override;

protected:
    static QScopedPointer<QPixmap> pmap;
    // The drawPixmap function must not modify pixmap size
    virtual void redraw(const QVariant&) const = 0;
};

template<unsigned int pixWidth, unsigned int pixHeight>
QScopedPointer<QPixmap> ScListBoxPixmap<pixWidth, pixHeight>::pmap;

template<unsigned int pixWidth, unsigned int pixHeight>
ScListBoxPixmap<pixWidth, pixHeight>::ScListBoxPixmap(void) : QAbstractItemDelegate()
{
    if (pmap.isNull())
        pmap.reset(new QPixmap(pixWidth, pixHeight));
}

template<unsigned int pixWidth, unsigned int pixHeight>
QSize ScListBoxPixmap<pixWidth, pixHeight>::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    int h,w;
    QFontMetrics metrics(option.font);
    const QVariant data(index.data(Qt::DisplayRole));

    QString textData = text(data);
    if (textData.isEmpty())
    {
        h = pmap->height();
        w = pmap->width() + 6;
    }
    else
    {
        h = qMax(pmap->height(), metrics.lineSpacing() + 2);
        w = pmap->width() + metrics.horizontalAdvance(textData) + 6;
    }

    return QSize(qMax(w, 0), qMax(h, 0));
}

template<unsigned int pixWidth, unsigned int pixHeight>
void ScListBoxPixmap<pixWidth, pixHeight>::paint(QPainter * qpainter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    const QVariant data(index.data(Qt::UserRole));
    redraw(data);

    int itemHeight = sizeHint(option, index).height();

    if (option.state & QStyle::State_Selected)
        qpainter->fillRect(option.rect, option.palette.highlight());

    qpainter->save();
    qpainter->setRenderHint(QPainter::Antialiasing, true);
    qpainter->setPen(Qt::NoPen);

    if (!pmap->isNull())
    {
        int yPos = (itemHeight - pmap->height()) / 2;
        qpainter->drawPixmap(option.rect.x() + 3, option.rect.y() + yPos, *pmap);
    }

    if (option.state & QStyle::State_Selected)
        qpainter->setPen(QPen(option.palette.highlightedText(), 0));
    else
        qpainter->setPen(QPen(option.palette.text(), 0));

    QString txt(index.data(Qt::DisplayRole).toString());
    if (!txt.isEmpty())
    {
        QFontMetrics fm = qpainter->fontMetrics();
        int yPos = (itemHeight - fm.height()) / 2 + fm.ascent();
        qpainter->drawText(option.rect.x() + pmap->width() + 5, option.rect.y() + yPos, txt);
    }
    qpainter->restore();
}

/* ********************************************************************************* *
 *
 * Small Item
 *
 * ********************************************************************************* */

class ColorSmallItemDelegate : public ScListBoxPixmap<16, 16>
{
public:
    ColorSmallItemDelegate(): ScListBoxPixmap<16, 16>() {};
    ~ColorSmallItemDelegate() = default;

    void redraw(const QVariant&) const ;
    QString text(const QVariant&) const ;
};

/* ********************************************************************************* *
 *
 * Wide Item
 *
 * ********************************************************************************* */

class ColorWideItemDelegate : public ScListBoxPixmap<32, 16>
{
public:
    ColorWideItemDelegate(): ScListBoxPixmap<32, 16>() {};
    ~ColorWideItemDelegate() = default;

    void redraw(const QVariant&) const ;
    QString text(const QVariant&) const ;
};

/* ********************************************************************************* *
 *
 * Fancy Item
 *
 * ********************************************************************************* */

class ColorFancyItemDelegate : public ScListBoxPixmap<70, 16>
{
public:
    ColorFancyItemDelegate(): ScListBoxPixmap<70, 16>() { iconSetChange();};
    ~ColorFancyItemDelegate() = default;

    void iconSetChange();
    void redraw(const QVariant&) const ;
    QString text(const QVariant&) const ;

private:
    QPixmap alertIcon;
    QPixmap cmykIcon;
    QPixmap rgbIcon;
    QPixmap labIcon;
    QPixmap spotIcon;
    QPixmap regIcon;
};

#endif // COLORLISTITEM_DELEGATE_H
