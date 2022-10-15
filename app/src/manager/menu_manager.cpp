#include "menu_manager.h"
#include "block_fill.h"
#include "block_stroke.h"
#include "icon_manager.h"
#include "mainwindow.h"

#include <QPainterPath>

MenuManager* MenuManager::m_instance = nullptr;

MenuManager::MenuManager(QObject *parent)
                             : QObject(parent)
{

}

MenuManager& MenuManager::instance()
{
    static MenuManager m_instance;
    return m_instance;
}

void MenuManager::setup(MainWindow *window)
{
    mainWindow = window;
    menuList = new QMap<QString, QMenu*>();

}

QMenu *MenuManager::menuWindow()
{
    return menuList->value("window");
}



void MenuManager::initRootMenu(QMenuBar *menu)
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
    initEditMenu();
}

void MenuManager::initFileMenu()
{

    menuList->value("file")->addAction(IconManager::instance().icon("file-document"), tr("New Document"), QKeySequence::New, mainWindow, &MainWindow::newDocument);
    menuList->value("file")->addAction(tr("Open Document"), QKeySequence::Open, mainWindow, &MainWindow::openDocument);


}

void MenuManager::initEditMenu()
{
    menuList->value("edit")->addAction(tr("Styles..."), QKeySequence(Qt::Key_F4), mainWindow, &MainWindow::openStyles);
}
