/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#include <QPainter>

#include "style_listview.h"

/* ********************************************************************************* *
 *
 * STYLE LIST VIEW
 *
 * ********************************************************************************* */


StyleListView::StyleListView(QWidget *parent) : QTreeWidget(parent)
{
}

void StyleListView::drawRow(QPainter *painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
    if (index.column() == 0)
    {
        QFont f(painter->font());
        f.setBold(static_cast<StyleListViewItem*>(itemFromIndex(index))->isDirty());
// 		p->setFont(f);
        QStyleOptionViewItem newopt(option);
        newopt.font = f;
        QTreeView::drawRow(painter, newopt, index);
        return;
    }
    QTreeView::drawRow(painter, option, index);
}


/* ********************************************************************************* *
 *
 * STYLE LIST VIEW ITEM
 *
 * ********************************************************************************* */

StyleListViewItem::StyleListViewItem(QTreeWidget *parent, const QString &text)
    : QTreeWidgetItem(parent),
    m_isRoot(true), m_isDirty(false)
{
    setFlags(flags() & ~Qt::ItemIsSelectable);
    setText(0, text);
}

StyleListViewItem::StyleListViewItem(QTreeWidgetItem *parent, const QString &text, const StyleType &rootName)
    : QTreeWidgetItem(parent),
    m_isRoot(false), m_isDirty(false),
    m_parentName(parent->text(0)), m_rootName(rootName)
{
    setText(0, text);
}


void StyleListViewItem::setDirty(bool isDirty)
{
    m_isDirty = isDirty;
}

bool StyleListViewItem::isDirty()
{
    return m_isDirty;
}

bool StyleListViewItem::isRoot()
{
    return m_isRoot;
}

QString StyleListViewItem::parentName()
{
    return m_parentName;
}

StyleType StyleListViewItem::rootName()
{
    return m_rootName;
}

