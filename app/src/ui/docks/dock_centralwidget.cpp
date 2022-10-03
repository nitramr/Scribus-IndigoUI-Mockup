#include "dock_centralwidget.h"

#include "component_documentselector.h"

DockCentralWidget::DockCentralWidget(QWidget *parent) : ads::CDockWidget(QString(), parent)
{

    ComponentDocumentSelector* selector = new ComponentDocumentSelector();

    setWidget(selector);
    setFeature(ads::CDockWidget::NoTab, true);
    setFeature(ads::CDockWidget::DockWidgetFloatable, false);
}

