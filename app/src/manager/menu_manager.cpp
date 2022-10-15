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
    // Root Menu
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

    IconManager &iconManager = IconManager::instance();

    QMenu * mFileImport = new QMenu(tr("Import"));
    QMenu * mFileExport = new QMenu(tr("Export"));
    QMenu * mFileOutputPreview = new QMenu(tr("Output Preview"));

    menuList->insert("file-import", mFileImport);
    menuList->insert("file-export", mFileExport);
    menuList->insert("file-outputpreview", mFileOutputPreview);

    menuList->value("file")->addAction( iconManager.icon("file-document"), tr("&New Document"), QKeySequence::New, mainWindow, &MainWindow::newDocument );
    menuList->value("file")->addAction( tr("New from Template"), QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_N) );
    menuList->value("file")->addAction( iconManager.icon("open"), tr("&Open Document"), QKeySequence::Open, mainWindow, &MainWindow::openDocument );
    menuList->value("file")->addAction( tr("Open Recent") );
    menuList->value("file")->addSeparator();
    menuList->value("file")->addAction( tr("&Close"), QKeySequence::Close );
    menuList->value("file")->addAction( iconManager.icon("save"), tr("&Save"), QKeySequence::Save );
    menuList->value("file")->addAction( iconManager.icon("save"), tr("Save &As"), QKeySequence::SaveAs );
    menuList->value("file")->addAction( tr("Save as &Template"), QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_S) );
    menuList->value("file")->addAction( tr("Re&vert to Saved") );
    menuList->value("file")->addAction( tr("Collect from O&utput") );
    menuList->value("file")->addSeparator();
    menuList->value("file")->addMenu( mFileImport );
    menuList->value("file")->addMenu( mFileExport );
    menuList->value("file")->addSeparator();
    menuList->value("file")->addAction( tr("Document Setup") );
    menuList->value("file")->addAction( tr("Preferences") );
    menuList->value("file")->addSeparator();
    menuList->value("file")->addAction( iconManager.icon("print"), tr("&Print"), QKeySequence::Print );
    menuList->value("file")->addAction( tr("Print Previe&w") );
    menuList->value("file")->addSeparator();
    menuList->value("file")->addMenu( mFileOutputPreview );
    menuList->value("file")->addSeparator();
    menuList->value("file")->addAction( tr("Quit"), QKeySequence::Quit );

    initFileImportMenu();
    initFileExportMenu();
    initFileOutputPreviewMenu();

}

void MenuManager::initFileImportMenu()
{
     menuList->value("file-import")->addAction( tr("Get Text"), QKeySequence(Qt::CTRL | Qt::Key_I) );
     menuList->value("file-import")->addAction( tr("Append Text") );
     menuList->value("file-import")->addAction( tr("Get Image"), QKeySequence(Qt::CTRL | Qt::Key_I) );
     menuList->value("file-import")->addAction( tr("Get Vector File") );
}

void MenuManager::initFileExportMenu()
{
    menuList->value("file-export")->addAction( tr("Save Text") );
    menuList->value("file-export")->addAction( tr("Save as EPS") );
    menuList->value("file-export")->addAction( tr("Save as PDF"), QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_P) );
    menuList->value("file-export")->addAction( tr("Save as Image"), QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_E) );
    menuList->value("file-export")->addAction( tr("Save as SVG") );
    menuList->value("file-export")->addAction( tr("Save as XPS") );
}

void MenuManager::initFileOutputPreviewMenu()
{
    menuList->value("file-outputpreview")->addAction( tr("PDF") );
    menuList->value("file-outputpreview")->addAction( tr("Postscript") );
}

void MenuManager::initEditMenu()
{
    menuList->value("edit")->addAction( tr("Styles"), QKeySequence(Qt::Key_F4), mainWindow, &MainWindow::openStyles );
}
