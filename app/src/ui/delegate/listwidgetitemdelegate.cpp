#include "listwidgetitemdelegate.h"

#include <QPainter>
#include <QRect>
#include <QApplication>


ListWidgetItemDelegate::ListWidgetItemDelegate(int iconSize, QObject *parent) : QAbstractItemDelegate (parent)
{
    m_iconSize = iconSize;
}

void ListWidgetItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const{

    int padding = 8;
    qreal margin = 4.5;
    int iconSize = m_iconSize;
    int radius = 2;
    QColor cHighlight = QApplication::palette().highlight().color();
    cHighlight.setAlphaF(0.2);

    QRect r = option.rect;
    QRectF rItem = option.rect;
    rItem = rItem.adjusted(margin, margin, -margin, -margin);

    QPen linePen(QApplication::palette().mid().color(), 1, Qt::SolidLine);
    QPen lineMarkedPen(QApplication::palette().highlight().color(), 1, Qt::SolidLine);
    QPen fontPen(QApplication::palette().text().color(), 1, Qt::SolidLine);

    QBrush fillNormal(QApplication::palette().alternateBase().color());
    QBrush fillSelected(cHighlight);


    painter->setRenderHint(QPainter::Antialiasing, true);


    if(option.state & QStyle::State_Selected){
        painter->setBrush( fillSelected );
        painter->setPen(lineMarkedPen);
        painter->drawRoundedRect(rItem, radius,radius);

    } else {
        painter->setBrush( fillNormal );
        painter->setPen(linePen);
        painter->drawRoundedRect(rItem, radius,radius);

    }

    // Item Data
    QIcon ic = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
    QString title = index.data(Qt::DisplayRole).toString();


    // Icon
    if (!ic.isNull()) {

        int hSpace = (option.rect.width() - iconSize) / 2;
        int vSpace = padding;

        QPoint p = option.rect.topLeft();
        r = QRect(p.x() + hSpace, p.y() + vSpace,iconSize, iconSize);

        ic.paint(painter, r);
    }

    // Label
    r = option.rect.adjusted(padding, padding + iconSize, -padding, -padding);
    painter->setPen(fontPen);
    painter->setFont(QFont());
    painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignBottom|Qt::AlignHCenter|Qt::TextWordWrap, title, &r);


}

QSize ListWidgetItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const{
    return option.rect.size();//QSize(128, 128);
}

int ListWidgetItemDelegate::iconSize()
{
    return m_iconSize;
}

void ListWidgetItemDelegate::setIconSize(int size)
{
    m_iconSize = size;
}

