#ifndef DOCK_PANELBASE_H
#define DOCK_PANELBASE_H

#include <DockWidget.h>

class DockPanelBase : public ads::CDockWidget
{
public:
    DockPanelBase(const QString &title, QWidget *parent = 0);
    DockPanelBase(const QString &title, QIcon icon, QWidget *parent = 0);

    void setWidget(QWidget *widget);

};

#endif // DOCK_PANELBASE_H
