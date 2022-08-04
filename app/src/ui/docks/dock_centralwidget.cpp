#include "dock_centralwidget.h"

#include "component_documentselector.h"

DockCentralWidget::DockCentralWidget(QWidget *parent) : ads::CDockWidget(QString("_emptyDock"), parent)
{

    ComponentDocumentSelector* selector = new ComponentDocumentSelector();

    setWidget(selector);
    setFeature(ads::CDockWidget::NoTab, true);// set the flag before adding the widget to dock manager
    setFeature(ads::CDockWidget::DockWidgetFloatable, false);
    setFeature(ads::CDockWidget::DockWidgetFloatable, false);
}

