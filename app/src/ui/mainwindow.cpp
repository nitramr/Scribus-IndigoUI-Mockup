#include "mainwindow.h"

#include "ui_mainwindow.h"

#include <QLabel>
#include <QPushButton>
#include <QSettings>
#include <QToolBar>
#include <QToolButton>
#include <dock_documentbase.h>
#include <file_utils.h>
#include "DockAreaWidget.h"
#include "DockAreaTitleBar.h"
#include "DockAreaTabBar.h"
#include "IconProvider.h"


#include "configuration_manager.h"
#include "dock_panelbase.h"
#include "newdocument_dialog.h"
#include "dock_manager.h"
#include "icon_manager.h"
#include "menu_manager.h"
#include "theme_manager.h"
#include "widget_manager.h"
#include "toolbar_manager.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , iconManager(IconManager::instance())
    , menuManager(MenuManager::instance())
    , themeManager(ThemeManager::instance())
    , widgetManager(WidgetManager::instance())
    , toolbarManager(ToolbarManager::instance())
{

    /* -------------------------------
     * Manager
     * ------------------------------- */

    // Don't change order of managers.

    // themeManager.setup(); // <-- setup is execute on SplashScreen, if you remove it there, enable it here!
    iconManager.setup(themeManager.isDark());
    menuManager.setup(this);
    widgetManager.setup();
    toolbarManager.setup(this);


    /* -------------------------------
     * ManinWindow settings
     * ------------------------------- */
    ui->setupUi(this);

    setContextMenuPolicy(Qt::NoContextMenu);

    /* -------------------------------
     * Menus
     * ------------------------------- */
    initMenu();

    /* -------------------------------
     * Toolbars
     * ------------------------------- */
    initToolBars();

    /* -------------------------------
     * Docks
     * ------------------------------- */

    // Documentation: https://github.com/githubuser0xFFFF/Qt-Advanced-Docking-System/blob/master/doc/user-guide.md
    ads::CDockManager::setConfigFlag(ads::CDockManager::AlwaysShowTabs, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::FloatingContainerHasWidgetIcon, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::FloatingContainerHasWidgetTitle, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::HideSingleCentralWidgetTitleBar, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::OpaqueSplitterResize, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::TabCloseButtonIsToolButton, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::AllTabsHaveCloseButton, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaDynamicTabsMenuButtonVisibility, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasCloseButton, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasUndockButton, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHideDisabledButtons, true);

    ads::CDockManager::iconProvider().registerCustomIcon(ads::TabCloseIcon, IconManager::instance().icon("close"));
    ads::CDockManager::iconProvider().registerCustomIcon(ads::DockAreaCloseIcon, IconManager::instance().icon("close"));
    ads::CDockManager::iconProvider().registerCustomIcon(ads::DockAreaMenuIcon, IconManager::instance().icon("menu-down"));
    ads::CDockManager::iconProvider().registerCustomIcon(ads::DockAreaUndockIcon, IconManager::instance().icon("dock-float"));


    dockManager = new DockManager(MenuManager::instance().menuWindow(),this);


    /* -------------------------------
     * Documents (Dummy)
     * ------------------------------- */
    auto* document1 = new DockDocumentBase("Document 1");
    auto* document2 = new DockDocumentBase("Document 2");


    // Center Panel
    dockManager->addDocument(document1);
    dockManager->addDocument(document2);


    //    QDockWidget *dockToolProperties = new QDockWidget();
    //    dockToolProperties->setAllowedAreas(Qt::NoDockWidgetArea);
    //    dockToolProperties->setFeatures(QDockWidget::NoDockWidgetFeatures);
    //    dockToolProperties->setFixedHeight(80);
    //    addDockWidget(Qt::TopDockWidgetArea, dockToolProperties);


    //    auto CustomButton = new QToolButton(areaRight);
    //    CustomButton->setToolTip(QObject::tr("Create Editor"));
    //    CustomButton->setIcon(iconManager->icon("plus", 48));
    //    CustomButton->setAutoRaise(true);

    //    auto TitleBar = areaRight->titleBar();
    //    int Index = TitleBar->indexOf(TitleBar->tabBar());
    //    TitleBar->insertWidget(Index + 1, CustomButton);



}

MainWindow::~MainWindow()
{
    delete ui;
}

/* ********************************************************************************* *
 *
 * Public Methods
 *
 * ********************************************************************************* */

void MainWindow::saveState()
{
    QSettings Settings(ConfigurationManager::files("app_layout"), QSettings::IniFormat);
    Settings.setValue("App/Geometry", QMainWindow::saveGeometry());
    Settings.setValue("App/State", QMainWindow::saveState());
    Settings.setValue("App/DockingState", dockManager->saveState());
}

void MainWindow::restoreState()
{
    QSettings Settings(ConfigurationManager::files("app_layout"), QSettings::IniFormat);
    QMainWindow::restoreGeometry(Settings.value("App/Geometry").toByteArray());
    QMainWindow::restoreState(Settings.value("App/State").toByteArray());
    dockManager->restoreState(Settings.value("App/DockingState").toByteArray());
}

/* ********************************************************************************* *
 *
 * Private Methods
 *
 * ********************************************************************************* */

void MainWindow::initMenu()
{
    menuManager.initRootMenu(ui->menubar);
}

void MainWindow::initToolBars()
{
    // Left Area
    this->addToolBar(Qt::LeftToolBarArea, toolbarManager.toolbarTools());

    // Top Area
//    this->addToolBar(Qt::TopToolBarArea, toolbarManager.toolbarQuickTools());
//    this->addToolBarBreak();
    this->addToolBar(Qt::TopToolBarArea, toolbarManager.toolbarEmptyProperties());
    this->addToolBar(Qt::TopToolBarArea, toolbarManager.toolbarArcProperties());

}

/* ********************************************************************************* *
 *
 * Public Slots
 *
 * ********************************************************************************* */

void MainWindow::dummySlot()
{
    // this is a dummy function
    qDebug() << "MainWindow::dummySlot";
}

void MainWindow::newDocument()
{
    qDebug() << "new Doc";

    NewDocumentDialog * dialogNewDocument = new NewDocumentDialog(this);
    if (dialogNewDocument->exec())
    {

    }

}

void MainWindow::openDocument()
{
    qDebug() << "open Doc";
}
