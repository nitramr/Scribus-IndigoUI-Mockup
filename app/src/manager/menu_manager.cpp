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
    QMenu * mFile = new QMenu( tr("File") );
    QMenu * mEdit = new QMenu( tr("Edit") );
    QMenu * mItem = new QMenu( tr("Item") );
    QMenu * mInsert = new QMenu( tr("Insert") );
    QMenu * mPage = new QMenu( tr("Page") );
    QMenu * mTable = new QMenu( tr("Table") );
    QMenu * mExtras = new QMenu (tr("Extras") );
    QMenu * mView = new QMenu( tr("View") );
    QMenu * mScript = new QMenu( tr("Script") );
    QMenu * mWindow = new QMenu( tr("Window") );
    QMenu * mHelp = new QMenu( tr("Help") );

    menuList->insert(MENU_FILE, mFile);
    menuList->insert(MENU_EDIT, mEdit);
    menuList->insert(MENU_ITEM, mItem);
    menuList->insert(MENU_INSERT, mInsert);
    menuList->insert(MENU_PAGE, mPage);
    menuList->insert(MENU_TABLE, mTable);
    menuList->insert(MENU_EXTRAS, mExtras);
    menuList->insert(MENU_VIEW, mView);
    menuList->insert(MENU_SCRIPT, mScript);
    menuList->insert(MENU_WINDOW, mWindow);
    menuList->insert(MENU_HELP, mHelp);

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

    initPageMenu();
}

void MenuManager::initFileMenu()
{

    IconManager &iconManager = IconManager::instance();

    QMenu * mFileImport = new QMenu(tr("Import"));
    QMenu * mFileExport = new QMenu(tr("Export"));
    QMenu * mFileOutputPreview = new QMenu(tr("Output Preview"));

    menuList->insert(MENU_FILE_IMPORT, mFileImport);
    menuList->insert(MENU_FILE_EXPORT, mFileExport);
    menuList->insert(MENU_FILE_OUTPUTPREVIEW, mFileOutputPreview);

    menuList->value(MENU_FILE)->addAction( iconManager.icon("file-document"), tr("&New Document"), QKeySequence::New, mainWindow, &MainWindow::newDocument );
    menuList->value(MENU_FILE)->addAction( tr("New from Template"), QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_N) );
    menuList->value(MENU_FILE)->addAction( iconManager.icon("open"), tr("&Open Document"), QKeySequence::Open, mainWindow, &MainWindow::openDocument );
    menuList->value(MENU_FILE)->addAction( tr("Open Recent") );
    menuList->value(MENU_FILE)->addSeparator();
    menuList->value(MENU_FILE)->addAction( tr("&Close"), QKeySequence::Close );
    menuList->value(MENU_FILE)->addAction( iconManager.icon("save"), tr("&Save"), QKeySequence::Save );
    menuList->value(MENU_FILE)->addAction( iconManager.icon("save"), tr("Save &As"), QKeySequence::SaveAs );
    menuList->value(MENU_FILE)->addAction( tr("Save as &Template"), QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_S) );
    menuList->value(MENU_FILE)->addAction( tr("Re&vert to Saved") );
    menuList->value(MENU_FILE)->addAction( tr("Collect from O&utput") );
    menuList->value(MENU_FILE)->addSeparator();
    menuList->value(MENU_FILE)->addMenu( mFileImport );
    menuList->value(MENU_FILE)->addMenu( mFileExport );
    menuList->value(MENU_FILE)->addSeparator();
    menuList->value(MENU_FILE)->addAction( tr("Document Setup") );
    menuList->value(MENU_FILE)->addAction( tr("Preferences") );
    menuList->value(MENU_FILE)->addSeparator();
    menuList->value(MENU_FILE)->addAction( iconManager.icon("print"), tr("&Print"), QKeySequence::Print );
    menuList->value(MENU_FILE)->addAction( tr("Print Previe&w") );
    menuList->value(MENU_FILE)->addSeparator();
    menuList->value(MENU_FILE)->addMenu( mFileOutputPreview );
    menuList->value(MENU_FILE)->addSeparator();
    menuList->value(MENU_FILE)->addAction( tr("Quit"), QKeySequence::Quit );

    initFileImportMenu();
    initFileExportMenu();
    initFileOutputPreviewMenu();

}

void MenuManager::initFileImportMenu()
{
    menuList->value(MENU_FILE_IMPORT)->addAction( tr("Get Text"), QKeySequence(Qt::CTRL | Qt::Key_I) );
    menuList->value(MENU_FILE_IMPORT)->addAction( tr("Append Text") );
    menuList->value(MENU_FILE_IMPORT)->addAction( tr("Get Image"), QKeySequence(Qt::CTRL | Qt::Key_I) );
    menuList->value(MENU_FILE_IMPORT)->addAction( tr("Get Vector File") );
}

void MenuManager::initFileExportMenu()
{
    menuList->value(MENU_FILE_EXPORT)->addAction( tr("Save Text") );
    menuList->value(MENU_FILE_EXPORT)->addAction( tr("Save as EPS") );
    menuList->value(MENU_FILE_EXPORT)->addAction( tr("Save as PDF"), QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_P) );
    menuList->value(MENU_FILE_EXPORT)->addAction( tr("Save as Image"), QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_E) );
    menuList->value(MENU_FILE_EXPORT)->addAction( tr("Save as SVG") );
    menuList->value(MENU_FILE_EXPORT)->addAction( tr("Save as XPS") );
}

void MenuManager::initFileOutputPreviewMenu()
{
    menuList->value(MENU_FILE_OUTPUTPREVIEW)->addAction( tr("PDF") );
    menuList->value(MENU_FILE_OUTPUTPREVIEW)->addAction( tr("Postscript") );
}

void MenuManager::initEditMenu()
{
    menuList->value(MENU_EDIT)->addAction( tr("Styles"), QKeySequence(Qt::Key_F4), mainWindow, &MainWindow::openStyles );
}

void MenuManager::initPageMenu()
{
    QAction *actionSnapToGrid = new QAction( tr("Sn&ap to Grid") );
    actionSnapToGrid->setCheckable(true);

    menuList->value(MENU_PAGE)->addAction( actionSnapToGrid );
}
