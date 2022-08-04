#include "dockmanager.h"

#include <dock_centralwidget.h>
#include <QMenu>
#include <dock_panelbase.h>

#include "iconmanager.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

DockManager::DockManager(QMenu *menu, QWidget *parent, QString theme) : ads::CDockManager(parent)
{

    setStyleSheet(theme);

    setupDocks();
    setupMenus(menu);

    loadDefaultWorkspace();

}

void DockManager::setupDocks()
{

    // Empty document area
    auto* emptyDock = new DockCentralWidget();
    areaCenter = setCentralWidget(emptyDock);
    areaCenter->setAllowedAreas(ads::DockWidgetArea::OuterDockAreas);

    // Create docks
    dockLayers = new DockPanelBase(tr("Layers"));
    dockPages = new DockPanelBase(tr("Pages"));
    dockContent = new DockPanelBase(tr("Content"));
    dockFrame = new DockPanelBase(tr("Frame"));
    dockOutliner = new DockPanelBase(tr("Outliner"));
    dockAlignDistribute = new DockPanelBase(tr("Align and Distribute"));
    //dockTest = new DockBase("Test");



    // Panel Frame Properties
    panelFrame = new PanelFrame();
    dockFrame->setWidget(panelFrame);

    // Panel Content Properties
    panelContent = new PanelContent();
    dockContent->setWidget(panelContent);

    // Panel Pages
    panelPages = new PanelPages();
    dockPages->setWidget(panelPages);

    // Panel Layers
    panelLayers= new PanelLayers();
    dockLayers->setWidget(panelLayers);

    // Panel Outliner
    panelOutliner= new PanelOutliner();
    dockOutliner->setWidget(panelOutliner);

    panelAlignDistribute = new PanelAlignDistribute();
    dockAlignDistribute->setWidget(panelAlignDistribute);


//    PanelTest * panelTest = new PanelTest();
    //    dockTest->setWidget(panelTest);
}

void DockManager::setupMenus(QMenu *menu)
{

    // Add docks to menue
    windowMenu = menu;
    windowMenu->addAction(dockContent->toggleViewAction());
    windowMenu->addAction(dockFrame->toggleViewAction());
    // Action History
    windowMenu->addAction(dockAlignDistribute->toggleViewAction());
    windowMenu->addSeparator();
    windowMenu->addAction(dockOutliner->toggleViewAction());
    windowMenu->addAction(dockPages->toggleViewAction());
    windowMenu->addAction(dockLayers->toggleViewAction());
    // Bookmarks
    // Resources
    windowMenu->addSeparator();
    // Scrapbook
    // Symbols
    // Inline Items
    // windowMenu->addSeparator();
    // Measurements
    // Preflight Verifier
    // windowMenu->addSeparator();
    // Tools
    // PDF Tools
    // View Tools
    // windowMenu->addSeparator();
    // Custom Shapes
}


/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

QMenu *DockManager::menu()
{
    return windowMenu;
}

/* ********************************************************************************* *
 *
 * Public Methods
 *
 * ********************************************************************************* */

ads::CDockAreaWidget* DockManager::addDocument(DockDocumentBase *document)
{
    auto * dockArea =  addDockWidget(ads::CenterDockWidgetArea, document, areaCenter);
    windowMenu->addAction(document->toggleViewAction());

    connect(document, &DockDocumentBase::changedContentMode, panelContent, &PanelContent::setContentMode);

    return dockArea;

}

void DockManager::loadDefaultWorkspace()
{
    // Left Panel
    auto * areaLeft = addDockWidget(ads::LeftDockWidgetArea, dockContent);
    addDockWidget(ads::CenterDockWidgetArea, dockPages, areaLeft);


    // Right Panel
    auto * areaRight = addDockWidget(ads::RightDockWidgetArea, dockFrame);
    auto * areaRightBottom = addDockWidget(ads::BottomDockWidgetArea, dockLayers, areaRight);
    addDockWidget(ads::CenterDockWidgetArea, dockOutliner, areaRightBottom);
    addDockWidget(ads::CenterDockWidgetArea, dockAlignDistribute, areaRightBottom);


    // Top Panel
    //auto * areaTop = addDockWidget(ads::TopDockWidgetArea, dockTest);
}

