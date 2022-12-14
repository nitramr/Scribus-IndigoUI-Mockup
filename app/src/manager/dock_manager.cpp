#include "dock_manager.h"

#include <dock_centralwidget.h>
#include <QMenu>
#include <dock_panelbase.h>

#include "icon_manager.h"

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
//    dockToolProperties = new DockPanelBase("Tool Properties");



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

    // Panel Alignment & Distribution
    panelAlignDistribute = new PanelAlignDistribute();
    dockAlignDistribute->setWidget(panelAlignDistribute);

    // Panel ToolProperties
//    PanelToolProperties * panelTest = new PanelToolProperties();
//    dockToolProperties->setWidget(panelTest);
//    dockToolProperties->setFeature(ads::CDockWidget::NoTab, true);
}

void DockManager::setupMenus(QMenu *menu)
{

    // Set Shortcuts
    dockFrame->toggleViewAction()->setShortcut( QKeySequence(Qt::Key_F2) );
    dockContent->toggleViewAction()->setShortcut( QKeySequence(Qt::Key_F3) );
    dockLayers->toggleViewAction()->setShortcut( QKeySequence(Qt::Key_F6) );



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
    addDockWidget(ads::CenterDockWidgetArea, dockOutliner, areaLeft);
    addDockWidget(ads::CenterDockWidgetArea, dockPages, areaLeft);


    // Right Panel
    auto * areaRight = addDockWidget(ads::RightDockWidgetArea, dockFrame);
    auto * areaRightBottom = addDockWidget(ads::BottomDockWidgetArea, dockLayers, areaRight);

    addDockWidget(ads::CenterDockWidgetArea, dockAlignDistribute, areaRightBottom);


    // Top Panel
//    auto * areaTop = addDockWidget(ads::TopDockWidgetArea, dockToolProperties);
//    areaTop->setAllowedAreas(ads::NoDockWidgetArea);
//    areaTop->setDockAreaFlag(ads::CDockAreaWidget::HideSingleWidgetTitleBar, true);

}

