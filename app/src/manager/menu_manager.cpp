#include "menu_manager.h"
#include "block_fill.h"
#include "block_stroke.h"
#include "mainwindow.h"
#include "icon_manager.h"
#include "shortcut_manager.h"

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
    ShortcutManager & shortcutManager = ShortcutManager::instance();

    QMenu * mFileImport = new QMenu(tr("Import"));
    QMenu * mFileExport = new QMenu(tr("Export"));
    QMenu * mFileOutputPreview = new QMenu(tr("Output Preview"));

    menuList->insert(MENU_FILE_IMPORT, mFileImport);
    menuList->insert(MENU_FILE_EXPORT, mFileExport);
    menuList->insert(MENU_FILE_OUTPUTPREVIEW, mFileOutputPreview);

    menuList->value(MENU_FILE)->addAction( iconManager.icon("file-document"),   tr("&New Document"),        shortcutManager.keySequence("fileNew"),             mainWindow, &MainWindow::newDocument );
    menuList->value(MENU_FILE)->addAction(                                      tr("New from Template"),    shortcutManager.keySequence("fileNewFromTemplate") );
    menuList->value(MENU_FILE)->addAction( iconManager.icon("open"),            tr("&Open Document"),       shortcutManager.keySequence("fileOpen"),            mainWindow, &MainWindow::openDocument );
    menuList->value(MENU_FILE)->addAction(                                      tr("Open Recent") );
    menuList->value(MENU_FILE)->addSeparator();
    menuList->value(MENU_FILE)->addAction(                                      tr("&Close"),               shortcutManager.keySequence("fileQuit") );
    menuList->value(MENU_FILE)->addAction( iconManager.icon("save"),            tr("&Save"),                shortcutManager.keySequence("fileSave") );
    menuList->value(MENU_FILE)->addAction( iconManager.icon("save"),            tr("Save &As"),             shortcutManager.keySequence("fileSaveAs") );
    menuList->value(MENU_FILE)->addAction(                                      tr("Save as &Template"),    shortcutManager.keySequence("SaveAsDocumentTemplate") );
    menuList->value(MENU_FILE)->addAction(                                      tr("Re&vert to Saved") );
    menuList->value(MENU_FILE)->addAction(                                      tr("Collect from O&utput") );
    menuList->value(MENU_FILE)->addSeparator();
    menuList->value(MENU_FILE)->addMenu( mFileImport );
    menuList->value(MENU_FILE)->addMenu( mFileExport );
    menuList->value(MENU_FILE)->addSeparator();
    menuList->value(MENU_FILE)->addAction(                                      tr("Document Setup") );
    menuList->value(MENU_FILE)->addAction(                                      tr("Preferences") );
    menuList->value(MENU_FILE)->addSeparator();
    menuList->value(MENU_FILE)->addAction( iconManager.icon("print"),           tr("&Print"),               shortcutManager.keySequence("filePrint") );
    menuList->value(MENU_FILE)->addAction(                                      tr("Print Previe&w") );
    menuList->value(MENU_FILE)->addSeparator();
    menuList->value(MENU_FILE)->addMenu( mFileOutputPreview );
    menuList->value(MENU_FILE)->addSeparator();
    menuList->value(MENU_FILE)->addAction(                                      tr("Quit"),                 shortcutManager.keySequence("fileQuit") );

    initFileImportMenu();
    initFileExportMenu();
    initFileOutputPreviewMenu();

}

void MenuManager::initFileImportMenu()
{
    ShortcutManager & shortcutManager = ShortcutManager::instance();

    menuList->value(MENU_FILE_IMPORT)->addAction( tr("Get Text"),       shortcutManager.keySequence("fileImportText") );
    menuList->value(MENU_FILE_IMPORT)->addAction( tr("Append Text") );
    menuList->value(MENU_FILE_IMPORT)->addAction( tr("Get Image"),      shortcutManager.keySequence("fileImportImage") );
    menuList->value(MENU_FILE_IMPORT)->addAction( tr("Get Vector File") );
}

void MenuManager::initFileExportMenu()
{
    ShortcutManager & shortcutManager = ShortcutManager::instance();

    menuList->value(MENU_FILE_EXPORT)->addAction( tr("Save Text") );
    menuList->value(MENU_FILE_EXPORT)->addAction( tr("Save as EPS") );
    menuList->value(MENU_FILE_EXPORT)->addAction( tr("Save as PDF"),    shortcutManager.keySequence("fileExportAsPDF") );
    menuList->value(MENU_FILE_EXPORT)->addAction( tr("Save as Image"),  shortcutManager.keySequence("ExportAsImage") );
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
    ShortcutManager & shortcutManager = ShortcutManager::instance();

    menuList->value(MENU_EDIT)->addAction( tr("Styles"), shortcutManager.keySequence("editStyles"), mainWindow, &MainWindow::openStyles );
}

void MenuManager::initPageMenu()
{
    QAction *actionSnapToGrid = new QAction( tr("Sn&ap to Grid") );
    actionSnapToGrid->setCheckable(true);

    menuList->value(MENU_PAGE)->addAction( actionSnapToGrid );
}
