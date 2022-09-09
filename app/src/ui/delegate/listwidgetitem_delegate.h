#ifndef LISTWIDGETITEM_DELEGATE_H
#define LISTWIDGETITEM_DELEGATE_H

#include <QAbstractItemDelegate>

class ListWidgetItemDelegate : public QAbstractItemDelegate
{
public:
    ListWidgetItemDelegate(int iconSize, QObject *parent = nullptr);
    virtual ~ListWidgetItemDelegate(){};

    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    int iconSize();
    void setIconSize(int size);

private:
    int m_iconSize = {64};
};


#endif // LISTWIDGETITEM_DELEGATE_H
