#include "outline_viewer.h"

OutlineTreeItem::OutlineTreeItem(OutlineTreeItem* parent, OutlineTreeItem* after) : QTreeWidgetItem(parent, after)
{

}

OutlineTreeItem::OutlineTreeItem(QTreeWidget* parent, OutlineTreeItem* after) : QTreeWidgetItem(parent, after)
{

}



OutlineViewer::OutlineViewer(QWidget* parent) : QTreeWidget(parent)
{
    setDragDropMode(QAbstractItemView::InternalMove);
}

