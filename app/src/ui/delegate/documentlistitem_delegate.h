#ifndef DOCUMENTLISTITEM_DELEGATE_H
#define DOCUMENTLISTITEM_DELEGATE_H

#include <QAbstractItemDelegate>

class DocumentListItemDelegate : public QAbstractItemDelegate
{
public:
    DocumentListItemDelegate(int iconSize, QObject *parent = nullptr);
    virtual ~DocumentListItemDelegate(){};

    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;

    QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    int iconSize();
    void setIconSize(int size);

private:
    int m_iconSize = {64};
};


#endif // DOCUMENTLISTITEM_DELEGATE_H
