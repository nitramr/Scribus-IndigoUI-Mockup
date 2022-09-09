#include "action_manager.h"
#include "icon_manager.h"
#include "mainwindow.h"

#include <QPainterPath>

ActionManager* ActionManager::m_instance = nullptr;

ActionManager::ActionManager(QObject *parent)
                             : QObject(parent)
{

}

ActionManager& ActionManager::instance()
{
    static ActionManager m_instance;
    return m_instance;
}

void ActionManager::setup(MainWindow *window)
{
    mainWindow = window;
    menuList = new QMap<QString, QMenu*>();

}

QMenu *ActionManager::menuWindow()
{
    return menuList->value("window");
}

void ActionManager::initToolBar(QToolBar *toolbar)
{
    // Selection
    toolbar->addAction(IconManager::instance().icon("tool-selection")       ,tr("Selection")        , mainWindow, &MainWindow::dummySlot);
    toolbar->addAction(IconManager::instance().icon("tool-edit")            ,tr("Edit")             , mainWindow, &MainWindow::dummySlot);
    toolbar->addSeparator();
    // Content
    toolbar->addAction(IconManager::instance().icon("tool-text-frame")      ,tr("Textbox")          , mainWindow, &MainWindow::dummySlot);
    toolbar->addAction(IconManager::instance().icon("tool-image")           ,tr("Image")            , mainWindow, &MainWindow::dummySlot);
    toolbar->addAction(IconManager::instance().icon("tool-render-frame")    ,tr("Render Frame")     , mainWindow, &MainWindow::dummySlot);
    toolbar->addAction(IconManager::instance().icon("tool-table")           ,tr("Table")            , mainWindow, &MainWindow::dummySlot);
    toolbar->addSeparator();
    // Path + Shapes
    toolbar->addAction(IconManager::instance().icon("tool-rectangle")       ,tr("Rectangle")        , mainWindow, &MainWindow::dummySlot);
    toolbar->addAction(IconManager::instance().icon("tool-star")            ,tr("Star")             , mainWindow, &MainWindow::dummySlot);
    toolbar->addAction(IconManager::instance().icon("tool-bezier")          ,tr("Bezier")           , mainWindow, &MainWindow::dummySlot);
    toolbar->addAction(IconManager::instance().icon("tool-pencil")          ,tr("Pen")              , mainWindow, &MainWindow::dummySlot);
    toolbar->addAction(IconManager::instance().icon("tool-calligraphy")     ,tr("Calligraphy")      , mainWindow, &MainWindow::dummySlot);
    toolbar->addSeparator();
    // Tools
    toolbar->addAction(IconManager::instance().icon("tool-gradient")        ,tr("Gradient Edit")    , mainWindow, &MainWindow::dummySlot);
    toolbar->addAction(IconManager::instance().icon("tool-zoom")            ,tr("Zoom")             , mainWindow, &MainWindow::dummySlot);    
    toolbar->addAction(IconManager::instance().icon("tool-text-link")       ,tr("Link Text Frames") , mainWindow, &MainWindow::dummySlot);
    toolbar->addAction(IconManager::instance().icon("tool-text-unlink")     ,tr("Unlink Text Frames"), mainWindow, &MainWindow::dummySlot);
    toolbar->addAction(IconManager::instance().icon("tool-measure")         ,tr("Measure")          , mainWindow, &MainWindow::dummySlot);
    toolbar->addAction(IconManager::instance().icon("tool-property-copy")   ,tr("Copy Item property"), mainWindow, &MainWindow::dummySlot);
    toolbar->addAction(IconManager::instance().icon("tool-eyedropper")      ,tr("Eye Dropper")      , mainWindow, &MainWindow::dummySlot);
    toolbar->addSeparator();
    // Plugins
    toolbar->addAction(IconManager::instance().icon("tool-barcode")         ,tr("Barcode")          , mainWindow, &MainWindow::dummySlot);

}

void ActionManager::initRootMenu(QMenuBar *menu)
{
    QMenu * mFile = new QMenu(tr("File"));
    QMenu * mEdit = new QMenu(tr("Edit"));
    QMenu * mItem = new QMenu(tr("Item"));
    QMenu * mInsert = new QMenu(tr("Insert"));
    QMenu * mPage = new QMenu(tr("Page"));
    QMenu * mTable = new QMenu(tr("Table"));
    QMenu * mExtras = new QMenu(tr("Extras"));
    QMenu * mView = new QMenu(tr("View"));
    QMenu * mScript = new QMenu(tr("Script"));
    QMenu * mWindow = new QMenu("Window");
    QMenu * mHelp = new QMenu(tr("Help"));

    menuList->insert("file", mFile);
    menuList->insert("edit", mEdit);
    menuList->insert("item", mItem);
    menuList->insert("insert", mInsert);
    menuList->insert("page", mPage);
    menuList->insert("table", mTable);
    menuList->insert("extras", mExtras);
    menuList->insert("view", mView);
    menuList->insert("script", mScript);
    menuList->insert("window", mWindow);
    menuList->insert("help", mHelp);

    menu->addMenu(mFile);
    menu->addMenu(mEdit);
    menu->addMenu(mItem);
    menu->addMenu(mInsert);
    menu->addMenu(mPage);
    menu->addMenu(mTable);
    menu->addMenu(mExtras);
    menu->addMenu(mView);
    menu->addMenu(mScript);
    menu->addMenu(mWindow);
    menu->addMenu(mHelp);

    initFileMenu();
}

void ActionManager::initFileMenu()
{

    menuList->value("file")->addAction(IconManager::instance().icon("file-document"), tr("New Document"), mainWindow, &MainWindow::newDocument, QKeySequence::New);
    menuList->value("file")->addAction(tr("Open Document"), mainWindow, &MainWindow::openDocument, QKeySequence::Open);


}
