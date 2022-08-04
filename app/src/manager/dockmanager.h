#ifndef DOCKMANAGER_H
#define DOCKMANAGER_H

#include <DockAreaWidget.h>
#include <DockManager.h>
#include <dock_panelbase.h>
#include <dock_documentbase.h>
#include "panel_aligndistribute.h"
#include "panel_content.h"
#include "panel_frame.h"
#include "panel_layers.h"
#include "panel_outliner.h"
#include "panel_pages.h"
#include "panel_test.h"


class DockManager : public ads::CDockManager
{
    Q_OBJECT

public:
    DockManager(QMenu *menu, QWidget *parent, QString theme = "" );

    QMenu *menu();

    ads::CDockAreaWidget*  addDocument(DockDocumentBase * document);

    void loadDefaultWorkspace();

private:
    ads::CDockAreaWidget * areaCenter;
    QMenu *windowMenu;

    DockPanelBase * dockContent;
    DockPanelBase * dockFrame;
    DockPanelBase * dockLayers;
    DockPanelBase * dockPages;
    DockPanelBase * dockOutliner;
    DockPanelBase * dockAlignDistribute;

    PanelFrame * panelFrame;
    PanelContent * panelContent;
    PanelPages * panelPages;
    PanelLayers * panelLayers;
    PanelOutliner * panelOutliner;
    PanelAlignDistribute * panelAlignDistribute;

    //DockBase * dockTest;

    void setupDocks();
    void setupMenus(QMenu *menu);

};

#endif // DOCKMANAGER_H
