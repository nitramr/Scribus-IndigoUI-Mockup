#include "dock_panelbase.h"

#include <QLabel>

DockPanelBase::DockPanelBase(const QString &title, QIcon icon, QWidget *parent)  : DockPanelBase(title, parent)
{
    this->setIcon(icon);    
}


DockPanelBase::DockPanelBase(const QString &title, QWidget *parent) : ads::CDockWidget(title, parent)
{

    QLabel *lblDummy = new QLabel("Add Widgets here!");

    setWidget(lblDummy);
}

void DockPanelBase::setWidget(QWidget *widget)
{
    ads::CDockWidget::setWidget(widget);

}


