#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
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
#include "action_manager.h"
#include "theme_manager.h"
#include "widget_manager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , iconManager(IconManager::instance())
    , actionManager(ActionManager::instance())
    , themeManager(ThemeManager::instance())
    , widgetManager(WidgetManager::instance())
{

    // Manager Setup
    actionManager.setup(this);
   // themeManager.setup(); // <-- setup is execute on SplashScreen, if you remove it there, enable it here!
    iconManager.setIconsForDarkMode(themeManager.isDark());
    iconManager.setup();

    widgetManager.setup();



    ui->setupUi(this);

    initMenu();
    initToolBars();

    // Documentation: https://github.com/githubuser0xFFFF/Qt-Advanced-Docking-System/blob/master/doc/user-guide.md
    ads::CDockManager::setConfigFlag(ads::CDockManager::AlwaysShowTabs, true);       
    ads::CDockManager::setConfigFlag(ads::CDockManager::FloatingContainerHasWidgetIcon, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::HideSingleCentralWidgetTitleBar, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::OpaqueSplitterResize, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::TabCloseButtonIsToolButton, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::AllTabsHaveCloseButton, false);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaDynamicTabsMenuButtonVisibility, true);
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasCloseButton, false);//<
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHasUndockButton, false);//<
    ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaHideDisabledButtons, true);//<

    ads::CDockManager::iconProvider().registerCustomIcon(ads::TabCloseIcon, IconManager::instance().icon("close"));
    ads::CDockManager::iconProvider().registerCustomIcon(ads::DockAreaCloseIcon, IconManager::instance().icon("close"));
    ads::CDockManager::iconProvider().registerCustomIcon(ads::DockAreaMenuIcon, IconManager::instance().icon("menu-down"));
    ads::CDockManager::iconProvider().registerCustomIcon(ads::DockAreaUndockIcon, IconManager::instance().icon("dock-float"));


    dockManager = new DockManager(ActionManager::instance().menuWindow(),this);


    auto* document1 = new DockDocumentBase("Document 1");
    auto* document2 = new DockDocumentBase("Document 2");


    // Center Panel
    dockManager->addDocument(document1);
    dockManager->addDocument(document2);


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

void MainWindow::initMenu()
{
    actionManager.initRootMenu(ui->menubar);
}

void MainWindow::initToolBars()
{


    QToolBar * toolMain = new QToolBar(this);
    toolMain->setOrientation(Qt::Vertical);
    toolMain->setToolButtonStyle(Qt::ToolButtonIconOnly);
    toolMain->setIconSize(QSize(24,24));

    actionManager.initToolBar(toolMain);

    this->addToolBar(Qt::LeftToolBarArea, toolMain);

}

void MainWindow::dummySlot()
{
    // this is a dummy function
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
