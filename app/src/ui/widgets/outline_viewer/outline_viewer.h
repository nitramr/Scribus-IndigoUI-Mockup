#ifndef OUTLINEVIEWER_H
#define OUTLINEVIEWER_H

#include "scribusdoc.h"
#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>


class OutlineTreeItem : public QTreeWidgetItem
{
public:
    OutlineTreeItem(OutlineTreeItem* parent, OutlineTreeItem* after);
    OutlineTreeItem(QTreeWidget* parent, OutlineTreeItem* after);
    ~OutlineTreeItem() {};

    //	PageItem *PageItemObject { nullptr };
    //	ScPage *PageObject { nullptr };
    ScribusDoc *DocObject { nullptr };
    int LayerID { -1 };
    int type { -1 }; //1=PageItem on Master Page,2=,3=PageItem,4=,5=,...
};



class OutlineViewer : public QTreeWidget
{
    Q_OBJECT
public:
    OutlineViewer(QWidget* parent);
    ~OutlineViewer() {};

  //  void selectItems(const QList<QTreeWidgetItem*>& items);

signals:

};

#endif // OUTLINEVIEWER_H
