/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#ifndef STYLELISTVIEW_H
#define STYLELISTVIEW_H


#include <QTreeWidget>


class StyleListView : public QTreeWidget
{
    Q_OBJECT
public:
    StyleListView(QWidget *parent);
// 	~StyleView();
protected:
// 	void contentsMousePressEvent(QMouseEvent *e);
// 	void mousePressEvent(QMouseEvent * event);
// 	void contentsMouseDoubleClickEvent(QMouseEvent *e);
    void drawRow(QPainter *painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
};


class StyleListViewItem : public QTreeWidgetItem
{
public:
    StyleListViewItem(QTreeWidget *parent, const QString &text);
    StyleListViewItem(QTreeWidgetItem *parent, const QString &text, const QString &rootName);
// 	~StyleViewItem();

// 	void paintCell(QPainter *p, const QColorGroup &cg, int column, int width, int align);

    bool isRoot();
    QString parentName();
    QString rootName();
    void setDirty(bool isDirty);
    bool isDirty();

private:
    bool m_isRoot;
    bool m_isDirty;
    QString m_parentName;
    QString m_rootName;
};


#endif // STYLELISTVIEW_H
