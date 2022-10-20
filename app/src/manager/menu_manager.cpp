#include "menu_manager.h"
#include "autoforms_menu/autoforms_menu.h"
#include "mainwindow.h"
#include "icon_manager.h"
#include "shortcut_manager.h"

#include <QPainterPath>

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

MenuManager* MenuManager::m_instance = nullptr;

MenuManager::MenuManager(QObject *parent)
    : QObject(parent)
{

}

QAction *MenuManager::getAction(const QString &label, QString iconKey, QString shortcutKey, bool checkable)
{
    IconManager &iconManager = IconManager::instance();

    QAction * action = new QAction(label);

    if(!iconKey.isEmpty())
        action->setIcon( iconManager.icon(iconKey) );

    if(!shortcutKey.isEmpty())
        action->setShortcut( getShortcut(shortcutKey) );

    action->setCheckable(checkable);

    return action;
}

QKeySequence MenuManager::getShortcut(QString key)
{
    ShortcutManager & shortcutManager = ShortcutManager::instance();
    return shortcutManager.keySequence(key);
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

/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

QMenu *MenuManager::menuWindow()
{
    return menuList->value(MENU_WINDOW);
}

/* ********************************************************************************* *
 *
 * Private Methods
 *
 * ********************************************************************************* */

void MenuManager::initRootMenu(QMenuBar *menu)
{
    // Root Menu
    QMenu * mFile   = new QMenu( tr("File") );
    QMenu * mEdit   = new QMenu( tr("Edit") );
    QMenu * mItem   = new QMenu( tr("Item") );
    QMenu * mInsert = new QMenu( tr("Insert") );
    QMenu * mPage   = new QMenu( tr("Page") );
    QMenu * mTable  = new QMenu( tr("Table") );
    QMenu * mExtras = new QMenu( tr("Extras") );
    QMenu * mView   = new QMenu( tr("View") );
    QMenu * mScript = new QMenu( tr("Script") );
    QMenu * mWindow = new QMenu( tr("Window") );
    QMenu * mHelp   = new QMenu( tr("Help") );

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

    // File
    initFileMenu();
    initFileImportMenu();
    initFileExportMenu();
    initFileOutputPreviewMenu();
    initFileRecentFiles();

    // Edit
    initEditMenu();
    initEditContentsMenu();

    // Item
    initItemMenu();
    initItemDuplicateTransformMenu();
    initItemGroupingMenu();
    initItemLockingMenu();
    initItemLevelMenu();
    initItemSendToLayerMenu();    
    initItemSendToMenu();
    initItemSendToScrapbookMenu();
    initItemAdjustMenu();
    initItemImageMenu();
    initItemImagePreviewSettingsMenu();
    initItemPDFOptionsMenu();
    initItemConvertToMenu();
    initItemTextFrameLinksMenu();

    // Insert
    initInsertMenu();
    initInsertCharacterMenu();
    initInsertQuoteMenu();
    initInsertSpacesBreaksMenu();
    initInsertLigatureMenu();
    initInsertMarksMenu();

    // Page
    initPageMenu();

    // Table
    initTableMenu();

    // Extras
    initExtrasMenu();

    // View
    initViewMenu();
    initViewZoomMenu();
    initViewPreviewMenu();
    initViewMeasurementMenu();
    initViewTextFramesMenu();
    initViewImageFramesMenu();
    initViewDocumentMenu();
    initViewGridsGuidesMenu();

    // Script
    initScriptMenu();
    initScriptScribusScripts();
    initScriptRecentScripts();

    // Help
    initHelpMenu();
}

/* ********************************************************************************* *
 *
 * FILE Menu
 *
 * ********************************************************************************* */

void MenuManager::initFileMenu()
{

    QMenu * mFileImport = new QMenu(tr("Import"));
    QMenu * mFileExport = new QMenu(tr("Export"));
    QMenu * mFileOutputPreview = new QMenu(tr("Output Preview"));
    QMenu * mFileRecentFiles = new QMenu(tr("Open Recent"));

    menuList->insert(MENU_FILE_IMPORT, mFileImport);
    menuList->insert(MENU_FILE_EXPORT, mFileExport);
    menuList->insert(MENU_FILE_OUTPUTPREVIEW, mFileOutputPreview);
    menuList->insert(MENU_FILE_RECENTFILES, mFileRecentFiles);

    menuList->value(MENU_FILE)->addAction( getAction( tr("&New Document"),          "file-document",    "fileNew",              false, mainWindow, &MainWindow::newDocument) );
    menuList->value(MENU_FILE)->addAction( getAction( tr("New from Template"),      "",                 "fileNewFromTemplate") );
    menuList->value(MENU_FILE)->addAction( getAction( tr("&Open Document"),         "open",             "fileOpen",             false, mainWindow, &MainWindow::openDocument) );
    menuList->value(MENU_FILE)->addMenu( mFileRecentFiles );
    menuList->value(MENU_FILE)->addSeparator();
    menuList->value(MENU_FILE)->addAction( getAction( tr("&Close"),                 "",                 "fileClose") );
    menuList->value(MENU_FILE)->addAction( getAction( tr("&Save"),                  "save",             "fileSave") );
    menuList->value(MENU_FILE)->addAction( getAction( tr("Save &As"),               "save",             "fileSaveAs") );
    menuList->value(MENU_FILE)->addAction( getAction( tr("Save as &Template"),      "",                 "SaveAsDocumentTemplate") );
    menuList->value(MENU_FILE)->addAction( getAction( tr("Re&vert to Saved"),       "",                 "fileRevert") );
    menuList->value(MENU_FILE)->addAction( getAction( tr("Collect from O&utput"),   "",                 "fileCollect") );
    menuList->value(MENU_FILE)->addSeparator();
    menuList->value(MENU_FILE)->addMenu( mFileImport );
    menuList->value(MENU_FILE)->addMenu( mFileExport );
    menuList->value(MENU_FILE)->addSeparator();
    menuList->value(MENU_FILE)->addAction( getAction( tr("Document Setup"),         "",                 "fileDocSetup150") );
    menuList->value(MENU_FILE)->addAction( getAction( tr("Preferences"),            "",                 "filePreferences150") );
    menuList->value(MENU_FILE)->addSeparator();
    menuList->value(MENU_FILE)->addAction( getAction( tr("&Print"),                 "print",            "filePrint") );
    menuList->value(MENU_FILE)->addAction( getAction( tr("Print Previe&w"),         "",                 "PrintPreview") );
    menuList->value(MENU_FILE)->addSeparator();
    menuList->value(MENU_FILE)->addMenu( mFileOutputPreview );
    menuList->value(MENU_FILE)->addSeparator();
    menuList->value(MENU_FILE)->addAction( getAction( tr("&Quit"),                  "",                 "fileQuit") );


}

void MenuManager::initFileImportMenu()
{
    menuList->value(MENU_FILE_IMPORT)->addAction( getAction( tr("Get Text"),        "", "fileImportText") );
    menuList->value(MENU_FILE_IMPORT)->addAction( getAction( tr("Append Text"),     "", "fileImportAppendText") );
    menuList->value(MENU_FILE_IMPORT)->addAction( getAction( tr("Get Image"),       "", "fileImportImage") );
    menuList->value(MENU_FILE_IMPORT)->addAction( getAction( tr("Get Vector File"), "", "fileImportVector") );

}

void MenuManager::initFileExportMenu()
{
    menuList->value(MENU_FILE_EXPORT)->addAction( getAction( tr("Save Text"),       "", "fileExportText") );
    menuList->value(MENU_FILE_EXPORT)->addAction( getAction( tr("Save as EPS"),     "", "fileExportAsEPS") );
    menuList->value(MENU_FILE_EXPORT)->addAction( getAction( tr("Save as PDF"),     "", "fileExportAsPDF") );
    menuList->value(MENU_FILE_EXPORT)->addAction( getAction( tr("Save as Image"),   "", "ExportAsImage") );
    menuList->value(MENU_FILE_EXPORT)->addAction( getAction( tr("Save as SVG"),     "", "ExportAsSVG") );
    menuList->value(MENU_FILE_EXPORT)->addAction( getAction( tr("Save as XPS"),     "", "ExportAsXPS") );
}

void MenuManager::initFileOutputPreviewMenu()
{
    menuList->value(MENU_FILE_OUTPUTPREVIEW)->addAction( getAction( tr("PDF"),          "", "OutputPreviewPDF") );
    menuList->value(MENU_FILE_OUTPUTPREVIEW)->addAction( getAction( tr("Postscript"),   "", "OutputPreviewPS") );
}

void MenuManager::initFileRecentFiles()
{
    menuList->value(MENU_FILE_RECENTFILES)->clear();

    // TODO: add logic to load recent files

}

/* ********************************************************************************* *
 *
 * EDIT Menu
 *
 * ********************************************************************************* */

void MenuManager::initEditMenu()
{

    QMenu * mEditContents = new QMenu( tr("Contents") );

    menuList->insert(MENU_EDIT_CONTENTS, mEditContents);

    menuList->value(MENU_EDIT)->addAction( getAction( tr("&Undo"),                  "undo",     "editUndoAction") );
    menuList->value(MENU_EDIT)->addAction( getAction( tr("&Redo"),                  "redo",     "editRedoAction") );
    menuList->value(MENU_EDIT)->addAction( getAction( tr("&Item Action Mode"),      "",         "", true) );
    menuList->value(MENU_EDIT)->addSeparator();
    menuList->value(MENU_EDIT)->addAction( getAction( tr("Cu&t"),                   "cut",      "editCut") );
    menuList->value(MENU_EDIT)->addAction( getAction( tr("&Copy"),                  "copy",     "editCopy") );
    menuList->value(MENU_EDIT)->addAction( getAction( tr("&Paste"),                 "paste",    "editPaste") );
    menuList->value(MENU_EDIT)->addAction( getAction( tr("&Delete"),                "delete",   "itemDelete") );
    menuList->value(MENU_EDIT)->addMenu( mEditContents );
    menuList->value(MENU_EDIT)->addSeparator();
    menuList->value(MENU_EDIT)->addAction( getAction( tr("Select &All"),            "",         "editSelectAll") );
    menuList->value(MENU_EDIT)->addAction( getAction( tr("Advanced Select All"),    "",         "editSelectAllOnLayer") );
    menuList->value(MENU_EDIT)->addAction( getAction( tr("&Deselect &All"),         "",         "editDeselectAll") );
    menuList->value(MENU_EDIT)->addSeparator();
    menuList->value(MENU_EDIT)->addAction( getAction( tr("&Search/Replace"),        "search",   "editSearchReplace") );
    menuList->value(MENU_EDIT)->addAction( getAction( tr("Edit Image"),             "", "") );
    menuList->value(MENU_EDIT)->addAction( getAction( tr("Edit Source"),            "", "") );
    menuList->value(MENU_EDIT)->addSeparator();
    menuList->value(MENU_EDIT)->addAction( getAction( tr("Colors && Fills"),        "",         "editColorsAndFills") );
    menuList->value(MENU_EDIT)->addAction( getAction( tr("Replace Colors"),         "",         "editReplaceColors") );
    menuList->value(MENU_EDIT)->addAction( getAction( tr("Styles"),                 "",         "editStyles", false, mainWindow, &MainWindow::openStyles) );
    menuList->value(MENU_EDIT)->addAction( getAction( tr("Marks"),                  "",         "editMarks") );
    menuList->value(MENU_EDIT)->addAction( getAction( tr("Parent Pages"),           "",         "editMasterPages") );
    menuList->value(MENU_EDIT)->addAction( getAction( tr("Javascript"),             "",         "editJavascripts") );


}

void MenuManager::initEditContentsMenu()
{
    menuList->value(MENU_EDIT_CONTENTS)->addAction( getAction( tr("Cu&t"),              "cut",      "editCut") );
    menuList->value(MENU_EDIT_CONTENTS)->addAction( getAction( tr("&Copy"),             "copy",     "editCopyContents") );
    menuList->value(MENU_EDIT_CONTENTS)->addAction( getAction( tr("&Paste"),            "paste",    "editPasteContents") );
    menuList->value(MENU_EDIT_CONTENTS)->addAction( getAction( tr("Paste (&Absolute)"), "paste",    "editPasteContentsAbs") );
    menuList->value(MENU_EDIT_CONTENTS)->addAction( getAction( tr("&Delete"),           "delete",   "editClearContents") );
    menuList->value(MENU_EDIT_CONTENTS)->addAction( getAction( tr("T&runcate"),         "",         "editTruncateContents") );

}

/* ********************************************************************************* *
 *
 * PAGE Menu
 *
 * ********************************************************************************* */

void MenuManager::initPageMenu()
{
    menuList->value(MENU_PAGE)->addAction( getAction( tr("&Insert"),                    "", "pageInsert") );
    menuList->value(MENU_PAGE)->addAction( getAction( tr("Imp&ort"),                    "", "pageImport") );
    menuList->value(MENU_PAGE)->addAction( getAction( tr("&Delete"),                    "", "pageDelete") );
    menuList->value(MENU_PAGE)->addAction( getAction( tr("&Copy"),                      "", "pageCopy") );
    menuList->value(MENU_PAGE)->addAction( getAction( tr("&Move"),                      "", "pageMove") );
    menuList->value(MENU_PAGE)->addSeparator();
    menuList->value(MENU_PAGE)->addAction( getAction( tr("&Apply Parent Page"),         "", "pageApplyMasterPage") );
    menuList->value(MENU_PAGE)->addAction( getAction( tr("Con&vert to Parent Page"),    "", "pageCopyToMasterPage") );
    menuList->value(MENU_PAGE)->addAction( getAction( tr("Manage &Guides"),             "", "pageManageGuides") );
    menuList->value(MENU_PAGE)->addAction( getAction( tr("Manage Page &Properties"),    "", "pageManageProperties") );
    menuList->value(MENU_PAGE)->addSeparator();
    menuList->value(MENU_PAGE)->addAction( getAction( tr("Snap to G&rid"),              "", "viewSnapToGrid", true) );
    menuList->value(MENU_PAGE)->addAction( getAction( tr("Snap to G&uides"),            "", "viewSnapToGuides", true) );
    menuList->value(MENU_PAGE)->addAction( getAction( tr("Snap to It&ems"),             "", "viewSnapToElements", true) );

}

/* ********************************************************************************* *
 *
 * ITEM Menu
 *
 * ********************************************************************************* */

void MenuManager::initItemMenu()
{
    QMenu * mItemDuplicateTransform = new QMenu(tr("Duplicate/Transform"));
    QMenu * mItemGrouping           = new QMenu(tr("Grouping"));
    QMenu * mItemLocking            = new QMenu(tr("Locking"));
    QMenu * mItemLevel              = new QMenu(tr("Level"));
    QMenu * mItemSendToLayer        = new QMenu(tr("Send to Layer"));
    QMenu * mItemSendTo             = new QMenu(tr("Send to"));
    QMenu * mItemAdjust             = new QMenu(tr("Adjust"));
    QMenu * mItemImage              = new QMenu(tr("Image"));
    QMenu * mItemPDFOptions         = new QMenu(tr("PDF Options"));
    QMenu * mItemConvertTo          = new QMenu(tr("Convert to"));
    QMenu * mItemTextFrameLinks     = new QMenu(tr("Text Frame Links"));
    QMenu * mItemPathTool           = new QMenu(tr("Path Tools"));
    QMenu * mItemWelding            = new QMenu(tr("Welding"));
    QMenu * mItemMarks              = new QMenu(tr("Marks"));
    QMenu * mItemTextFeatures       = new QMenu(tr("Text Features"));

    menuList->insert(MENU_ITEM_DUPLICATETRANSFORM, mItemDuplicateTransform);
    menuList->insert(MENU_ITEM_GROUPING, mItemGrouping);
    menuList->insert(MENU_ITEM_LOCKING, mItemLocking);
    menuList->insert(MENU_ITEM_LEVEL, mItemLevel);
    menuList->insert(MENU_ITEM_SENDTOLAYER, mItemSendToLayer);
    menuList->insert(MENU_ITEM_SENDTO, mItemSendTo);
    menuList->insert(MENU_ITEM_ADJUST, mItemAdjust);
    menuList->insert(MENU_ITEM_IMAGE, mItemImage);
    menuList->insert(MENU_ITEM_PDFOPTIONS, mItemPDFOptions);
    menuList->insert(MENU_ITEM_CONVERTTO, mItemConvertTo);
    menuList->insert(MENU_ITEM_TEXTFRAMELINKS, mItemTextFrameLinks);
    menuList->insert(MENU_ITEM_PATHTOOLS, mItemPathTool);
    menuList->insert(MENU_ITEM_WELDING, mItemWelding);
    menuList->insert(MENU_ITEM_MARKS, mItemMarks);
    menuList->insert(MENU_ITEM_TEXTFEATURE, mItemTextFeatures);

    menuList->value(MENU_ITEM)->addMenu( mItemDuplicateTransform );
    menuList->value(MENU_ITEM)->addMenu( mItemGrouping );
    menuList->value(MENU_ITEM)->addMenu( mItemLocking );
    menuList->value(MENU_ITEM)->addMenu( mItemLevel );
    menuList->value(MENU_ITEM)->addMenu( mItemSendToLayer );
    menuList->value(MENU_ITEM)->addMenu( mItemSendTo );
    menuList->value(MENU_ITEM)->addMenu( mItemAdjust );
    menuList->value(MENU_ITEM)->addMenu( mItemImage );
    menuList->value(MENU_ITEM)->addMenu( mItemPDFOptions );
    menuList->value(MENU_ITEM)->addMenu( mItemConvertTo );
    menuList->value(MENU_ITEM)->addMenu( mItemTextFrameLinks );
    menuList->value(MENU_ITEM)->addMenu( mItemPathTool );
    menuList->value(MENU_ITEM)->addMenu( mItemWelding );
    menuList->value(MENU_ITEM)->addMenu( mItemMarks );
    menuList->value(MENU_ITEM)->addMenu( mItemTextFeatures );

}

void MenuManager::initItemDuplicateTransformMenu()
{
    menuList->value(MENU_ITEM_DUPLICATETRANSFORM)->addAction( getAction( tr("&Duplicate"),           "", "itemDuplicate") );
    menuList->value(MENU_ITEM_DUPLICATETRANSFORM)->addAction( getAction( tr("&Multiple Duplicate"),  "", "itemMulDuplicate") );
    menuList->value(MENU_ITEM_DUPLICATETRANSFORM)->addAction( getAction( tr("&Transform"),           "", "itemTransform") );
}

void MenuManager::initItemGroupingMenu()
{
    menuList->value(MENU_ITEM_GROUPING)->addAction( getAction( tr("&Group"),        "", "itemGroup") );
    menuList->value(MENU_ITEM_GROUPING)->addAction( getAction( tr("&Ungroup"),      "", "itemUngroup") );
    menuList->value(MENU_ITEM_GROUPING)->addAction( getAction( tr("&Adjust Group"), "", "itemGroupAdjust") );
}

void MenuManager::initItemLockingMenu()
{
    menuList->value(MENU_ITEM_LOCKING)->addAction( getAction( tr("Is &Locked"),      "", "itemLock",     true) );
    menuList->value(MENU_ITEM_LOCKING)->addAction( getAction( tr("&Size is Locked"), "", "itemLockSize", true) );
}

void MenuManager::initItemLevelMenu()
{
    menuList->value(MENU_ITEM_LEVEL)->addAction( getAction( tr("To &Foreground"),    "level-foreground", "itemRaiseToTop") );
    menuList->value(MENU_ITEM_LEVEL)->addAction( getAction( tr("&Raise"),            "level-up",         "itemRaise") );
    menuList->value(MENU_ITEM_LEVEL)->addAction( getAction( tr("&Lower"),            "level-down",       "itemLower") );
    menuList->value(MENU_ITEM_LEVEL)->addAction( getAction( tr("To &Background"),    "level-background", "itemLowerToBottom") );
}

void MenuManager::initItemSendToLayerMenu()
{
    menuList->value(MENU_ITEM_SENDTOLAYER)->clear();
    menuList->value(MENU_ITEM_SENDTOLAYER)->addAction( getAction( tr("Background"), "", "") );

    // TODO: add logic to load recent files
}

void MenuManager::initItemSendToMenu()
{
    QMenu * mItemSendToScrapbook = new QMenu(tr("&Scrapbook"));

    menuList->insert(MENU_ITEM_SENDTO_SCRAPBOOK, mItemSendToScrapbook);

    menuList->value(MENU_ITEM_SENDTO)->addMenu( mItemSendToScrapbook );
    menuList->value(MENU_ITEM_SENDTO)->addAction( getAction( tr("&Patterns"),        "", "itemSendToPattern") );
    menuList->value(MENU_ITEM_SENDTO)->addAction( getAction( tr("&Inline-Items"),    "", "itemSendToInline") );
}

void MenuManager::initItemSendToScrapbookMenu()
{
    menuList->value(MENU_ITEM_SENDTO_SCRAPBOOK)->clear();
    // TODO: add logic to load scrapbook files
}

void MenuManager::initItemAdjustMenu()
{
    menuList->value(MENU_ITEM_ADJUST)->addAction( getAction( tr("Adjust Frame &Height to Text"), "", "itemAdjustFrameHeightToText") );
    menuList->value(MENU_ITEM_ADJUST)->addAction( getAction( tr("Adjust &Frame to Image"),       "", "itemAdjustFrameToImage") );
    menuList->value(MENU_ITEM_ADJUST)->addAction( getAction( tr("Adjust &Image to Frame"),       "", "itemAdjustImageToFrame") );
}

void MenuManager::initItemImageMenu()
{
    QMenu * mItemImagePreviewSettings = new QMenu(tr("Preview &Settings"));

    menuList->insert(MENU_ITEM_IMAGE_PREVIEWSETTINGS, mItemImagePreviewSettings);

    menuList->value(MENU_ITEM_IMAGE)->addAction( getAction( tr("&Update Image"),                 "", "itemUpdateImage") );
    menuList->value(MENU_ITEM_IMAGE)->addAction( getAction( tr("Extended Image &Properties"),    "", "itemExtendedImageProperties") );
    menuList->value(MENU_ITEM_IMAGE)->addAction( getAction( tr("&Embed Image"),               "", "", true) );
    menuList->value(MENU_ITEM_IMAGE)->addMenu( mItemImagePreviewSettings );
}

void MenuManager::initItemImagePreviewSettingsMenu()
{
    menuList->value(MENU_ITEM_IMAGE_PREVIEWSETTINGS)->addAction( getAction( tr("Image &Visible"),       "", "itemImageIsVisible", true) );
    menuList->value(MENU_ITEM_IMAGE_PREVIEWSETTINGS)->addSeparator();
    menuList->value(MENU_ITEM_IMAGE_PREVIEWSETTINGS)->addAction( getAction( tr("&Full Resolution"),     "", "itemPreviewFull") );
    menuList->value(MENU_ITEM_IMAGE_PREVIEWSETTINGS)->addAction( getAction( tr("&Normal Resolution"),   "", "itemPreviewNormal") );
    menuList->value(MENU_ITEM_IMAGE_PREVIEWSETTINGS)->addAction( getAction( tr("&Low Resolution"),      "", "itemPreviewLow") );
}

void MenuManager::initItemPDFOptionsMenu()
{
    menuList->value(MENU_ITEM_PDFOPTIONS)->addAction( getAction( tr("Is PDF &Annotation"),       "", "itemPDFIsAnnotation", true) );
    menuList->value(MENU_ITEM_PDFOPTIONS)->addAction( getAction( tr("Is PDF &Bookmark"),         "", "itemPDFIsBookmark", true) );
    menuList->value(MENU_ITEM_PDFOPTIONS)->addAction( getAction( tr("A&nnotation Properties"),   "", "itemPDFAnnotationProps") );
    menuList->value(MENU_ITEM_PDFOPTIONS)->addAction( getAction( tr("&Field Properties"),        "", "itemPDFFieldProps") );
}

void MenuManager::initItemConvertToMenu()
{
    menuList->value(MENU_ITEM_CONVERTTO)->addAction( getAction( tr("&Text Frame"),   "", "itemConvertToTextFrame") );
    menuList->value(MENU_ITEM_CONVERTTO)->addAction( getAction( tr("&Image Frame"),  "", "itemConvertToImageFrame") );
    menuList->value(MENU_ITEM_CONVERTTO)->addAction( getAction( tr("&Polygon"),      "", "itemConvertToPolygon") );
    menuList->value(MENU_ITEM_CONVERTTO)->addAction( getAction( tr("&Bezier Curve"), "", "itemConvertToBezierCurve") );
    menuList->value(MENU_ITEM_CONVERTTO)->addAction( getAction( tr("&Outlines"),     "", "itemConvertToOutlines") );
    menuList->value(MENU_ITEM_CONVERTTO)->addAction( getAction( tr("&Symbol"),       "", "itemConvertToSymbolFrame") );
}

void MenuManager::initItemTextFrameLinksMenu()
{
    menuList->value(MENU_ITEM_TEXTFRAMELINKS)->addAction( getAction( tr("&Link Text Frame"),                "tool-text-link",   "toolsLinkTextFrame") );
    menuList->value(MENU_ITEM_TEXTFRAMELINKS)->addAction( getAction( tr("&Unlink Text Frame"),              "tool-text-unlink", "toolsUnlinkTextFrame") );
    menuList->value(MENU_ITEM_TEXTFRAMELINKS)->addAction( getAction( tr("Unlink Text Frame and &Cut Text"), "",                 "toolsUnlinkTextFrameAndCutText") );
}

/* ********************************************************************************* *
 *
 * INSERT Menu
 *
 * ********************************************************************************* */

void MenuManager::initInsertMenu()
{
    AutoFormsMenu *mInsertShape = new AutoFormsMenu( tr("Shapes"), "tool-rectangle" );
    QMenu * mInsertCharacter = new QMenu( tr("Character") );
    QMenu * mInsertQuote = new QMenu( tr("&Quote") );
    QMenu * mInsertSpacesBreaks = new QMenu( tr("Spaces && Breaks") );
    QMenu * mInsertLigature = new QMenu( tr("Ligature") );
    QMenu * mInsertMarks = new QMenu( tr("Marks") );

    menuList->insert(MENU_INSERT_SHAPE, mInsertShape);
    menuList->insert(MENU_INSERT_CHARACTER, mInsertCharacter);
    menuList->insert(MENU_INSERT_QUOTE, mInsertQuote);
    menuList->insert(MENU_INSERT_SPACESBREAKS, mInsertSpacesBreaks);
    menuList->insert(MENU_INSERT_LIGATURE, mInsertLigature);
    menuList->insert(MENU_INSERT_MARKS, mInsertMarks);

    menuList->value(MENU_INSERT)->addAction( getAction( tr("Fra&mes"),              "",                     "") );
    menuList->value(MENU_INSERT)->addSeparator();
    menuList->value(MENU_INSERT)->addAction( getAction( tr("&Text Frame"),          "tool-text-frame",      "toolsInsertTextFrame") );
    menuList->value(MENU_INSERT)->addAction( getAction( tr("&Image Frame"),         "tool-image",           "toolsInsertImageFrame") );
    menuList->value(MENU_INSERT)->addAction( getAction( tr("&Render Frame"),        "tool-render-frame",    "toolsInsertRenderFrame") );
    menuList->value(MENU_INSERT)->addAction( getAction( tr("Tabl&e"),               "tool-table",           "toolsInsertTable") );
    QAction *actionShape = menuList->value(MENU_INSERT)->addMenu(mInsertShape);
    actionShape->setShortcut( getShortcut("toolsInsertShape") );
    menuList->value(MENU_INSERT)->addAction( getAction( tr("&Polygon"),             "tool-star",            "toolsInsertPolygon") );
    menuList->value(MENU_INSERT)->addAction( getAction( tr("&Arc"),                 "tool-arc",             "toolsInsertArc") );
    menuList->value(MENU_INSERT)->addAction( getAction( tr("Sprial"),               "tool-spiral",          "toolsInsertSpiral") );
    menuList->value(MENU_INSERT)->addAction( getAction( tr("&Line"),                "tool-line",            "toolsInsertLine") );
    menuList->value(MENU_INSERT)->addAction( getAction( tr("&Bezier Curve"),        "tool-bezier",          "toolsInsertBezier") );
    menuList->value(MENU_INSERT)->addAction( getAction( tr("&Freehand Line"),       "tool-pencil",          "toolsInsertFreehandLine") );
    menuList->value(MENU_INSERT)->addAction( getAction( tr("&Calligraphic Line"),   "tool-calligraphy",     "toolsInsertCalligraphicLine") );
    menuList->value(MENU_INSERT)->addAction( getAction( tr("Barco&de"),             "tool-barcode",         "") );
    menuList->value(MENU_INSERT)->addSeparator();
    menuList->value(MENU_INSERT)->addAction( getAction( tr("Stic&ky Tools"),        "",                     "", true) );
    menuList->value(MENU_INSERT)->addSeparator();
    menuList->value(MENU_INSERT)->addAction( getAction( tr("Gl&yphs"),              "",                     "") );
    menuList->value(MENU_INSERT)->addMenu(mInsertCharacter);
    menuList->value(MENU_INSERT)->addMenu(mInsertQuote);
    menuList->value(MENU_INSERT)->addMenu(mInsertSpacesBreaks);
    menuList->value(MENU_INSERT)->addMenu(mInsertLigature);
    menuList->value(MENU_INSERT)->addSeparator();
    menuList->value(MENU_INSERT)->addAction( getAction( tr("Sample Te&xt"),         "",                     "") );
    menuList->value(MENU_INSERT)->addMenu(mInsertMarks);
}

void MenuManager::initInsertCharacterMenu()
{
    menuList->value(MENU_INSERT_CHARACTER)->addAction( getAction( tr("Page &Number"),           "", "unicodePageNumber") );
    menuList->value(MENU_INSERT_CHARACTER)->addAction( getAction( tr("Number of &Pages"),       "", "unicodePageCount") );
    menuList->value(MENU_INSERT_CHARACTER)->addAction( getAction( tr("Soft &Hyphen"),           "", "unicodeSoftHyphen") );
    menuList->value(MENU_INSERT_CHARACTER)->addAction( getAction( tr("Non &Breaking Hyphen"),   "", "unicodeNonBreakingHyphen") );
    menuList->value(MENU_INSERT_CHARACTER)->addAction( getAction( tr("Zero Width &Joiner"),     "", "unicodeZWJ") );
    menuList->value(MENU_INSERT_CHARACTER)->addAction( getAction( tr("Zero &Width Non-Joiner"), "", "unicodeZWNJ") );
    menuList->value(MENU_INSERT_CHARACTER)->addSeparator();
    menuList->value(MENU_INSERT_CHARACTER)->addAction( getAction( tr("&Copyright"),             "", "unicodeCopyRight") );
    menuList->value(MENU_INSERT_CHARACTER)->addAction( getAction( tr("&Registered Trademark"),  "", "unicodeRegdTM") );
    menuList->value(MENU_INSERT_CHARACTER)->addAction( getAction( tr("&Trademark"),             "", "unicodeTM") );
    menuList->value(MENU_INSERT_CHARACTER)->addAction( getAction( tr("&Solidus"),               "", "unicodeSolidus") );
    menuList->value(MENU_INSERT_CHARACTER)->addAction( getAction( tr("&Bullet"),                "", "unicodeBullet") );
    menuList->value(MENU_INSERT_CHARACTER)->addAction( getAction( tr("&Middle Dot"),            "", "unicodeMidpoint") );
    menuList->value(MENU_INSERT_CHARACTER)->addSeparator();
    menuList->value(MENU_INSERT_CHARACTER)->addAction( getAction( tr("Em &Dash"),               "", "unicodeDashEm") );
    menuList->value(MENU_INSERT_CHARACTER)->addAction( getAction( tr("&En Dash"),               "", "unicodeDashEn") );
    menuList->value(MENU_INSERT_CHARACTER)->addAction( getAction( tr("&Figure Dash"),           "", "unicodeDashFigure") );
    menuList->value(MENU_INSERT_CHARACTER)->addAction( getAction( tr("&Quotation Dash"),        "", "unicodeDashQuotation") );
}

void MenuManager::initInsertQuoteMenu()
{
    menuList->value(MENU_INSERT_QUOTE)->addAction( getAction( tr("Apostrophe"),             "", "unicodeQuoteApostrophe") );
    menuList->value(MENU_INSERT_QUOTE)->addAction( getAction( tr("Straight Double"),        "", "unicodeQuoteStraight") );
    menuList->value(MENU_INSERT_QUOTE)->addSeparator();
    menuList->value(MENU_INSERT_QUOTE)->addAction( getAction( tr("Single Left"),            "", "unicodeQuoteSingleLeft") );
    menuList->value(MENU_INSERT_QUOTE)->addAction( getAction( tr("Single Right"),           "", "unicodeQuoteSingleRight") );
    menuList->value(MENU_INSERT_QUOTE)->addAction( getAction( tr("Double Left"),            "", "unicodeQuoteDoubleLeft") );
    menuList->value(MENU_INSERT_QUOTE)->addAction( getAction( tr("Double Right"),           "", "unicodeQuoteDoubleRight") );
    menuList->value(MENU_INSERT_QUOTE)->addSeparator();
    menuList->value(MENU_INSERT_QUOTE)->addAction( getAction( tr("Single Reverse"),         "", "unicodeQuoteSingleReversed") );
    menuList->value(MENU_INSERT_QUOTE)->addAction( getAction( tr("Double Reverse"),         "", "unicodeQuoteDoubleReversed") );
    menuList->value(MENU_INSERT_QUOTE)->addSeparator();
    menuList->value(MENU_INSERT_QUOTE)->addAction( getAction( tr("Low Single Comma"),       "", "unicodeQuoteLowSingleComma") );
    menuList->value(MENU_INSERT_QUOTE)->addAction( getAction( tr("Low Double Comma"),       "", "unicodeQuoteLowDoubleComma") );
    menuList->value(MENU_INSERT_QUOTE)->addSeparator();
    menuList->value(MENU_INSERT_QUOTE)->addAction( getAction( tr("Single Left Guillemet"),  "", "unicodeQuoteSingleLeftGuillemet") );
    menuList->value(MENU_INSERT_QUOTE)->addAction( getAction( tr("Single Right Guillemet"), "", "unicodeQuoteSingleRightGuillemet") );
    menuList->value(MENU_INSERT_QUOTE)->addAction( getAction( tr("Double Left Guillemet"),  "", "unicodeQuoteDoubleLeftGuillemet") );
    menuList->value(MENU_INSERT_QUOTE)->addAction( getAction( tr("Double Right Guillemet"), "", "unicodeQuoteDoubleRightGuillemet") );
    menuList->value(MENU_INSERT_QUOTE)->addSeparator();
    menuList->value(MENU_INSERT_QUOTE)->addAction( getAction( tr("CJK Single Left"),        "", "unicodeQuoteCJKSingleLeft") );
    menuList->value(MENU_INSERT_QUOTE)->addAction( getAction( tr("CJK Single Right"),       "", "unicodeQuoteCJKSingleRight") );
    menuList->value(MENU_INSERT_QUOTE)->addAction( getAction( tr("CJK Double Left"),        "", "unicodeQuoteCJKDoubleLeft") );
    menuList->value(MENU_INSERT_QUOTE)->addAction( getAction( tr("CJK Double Right"),       "", "unicodeQuoteCJKDoubleRight") );

}

void MenuManager::initInsertSpacesBreaksMenu()
{
    menuList->value(MENU_INSERT_SPACESBREAKS)->addAction( getAction( tr("Non &Breaking Space"),      "", "unicodeNonBreakingSpace") );
    menuList->value(MENU_INSERT_SPACESBREAKS)->addAction( getAction( tr("Narrow No-Break &Space"),   "", "unicodeNarrowNoBreakSpace") );
    menuList->value(MENU_INSERT_SPACESBREAKS)->addAction( getAction( tr("E&m Space"),                "", "unicodeSpaceEM") );
    menuList->value(MENU_INSERT_SPACESBREAKS)->addAction( getAction( tr("E&n Space"),                "", "unicodeSpaceEN") );
    menuList->value(MENU_INSERT_SPACESBREAKS)->addAction( getAction( tr("&Thin Space"),              "", "unicodeSpaceThin") );
    menuList->value(MENU_INSERT_SPACESBREAKS)->addAction( getAction( tr("Thick Space"),             "", "unicodeSpaceThick") );
    menuList->value(MENU_INSERT_SPACESBREAKS)->addAction( getAction( tr("&Mid Space"),               "", "unicodeSpaceMid") );
    menuList->value(MENU_INSERT_SPACESBREAKS)->addAction( getAction( tr("&Hair Space"),              "", "unicodeSpaceHair") );
    menuList->value(MENU_INSERT_SPACESBREAKS)->addSeparator();
    menuList->value(MENU_INSERT_SPACESBREAKS)->addAction( getAction( tr("&Zero Width Space"),        "", "unicodeZerowidthSpace") );
    menuList->value(MENU_INSERT_SPACESBREAKS)->addAction( getAction( tr("Ne&w Line"),                "", "unicodeNewLine") );
    menuList->value(MENU_INSERT_SPACESBREAKS)->addAction( getAction( tr("&Column Break"),            "", "unicodeColumnBreak") );
    menuList->value(MENU_INSERT_SPACESBREAKS)->addAction( getAction( tr("&Frame Break"),             "", "unicodeFrameBreak") );

}

void MenuManager::initInsertLigatureMenu()
{
    menuList->value(MENU_INSERT_LIGATURE)->addAction( getAction( tr("ff"),  "", "unicodeLigature_ff") );
    menuList->value(MENU_INSERT_LIGATURE)->addAction( getAction( tr("fi"),  "", "unicodeLigature_fi") );
    menuList->value(MENU_INSERT_LIGATURE)->addAction( getAction( tr("fl"),  "", "unicodeLigature_fl") );
    menuList->value(MENU_INSERT_LIGATURE)->addAction( getAction( tr("ffi"), "", "unicodeLigature_ffi") );
    menuList->value(MENU_INSERT_LIGATURE)->addAction( getAction( tr("ffl"), "", "unicodeLigature_ffl") );
    menuList->value(MENU_INSERT_LIGATURE)->addAction( getAction( tr("ft"),  "", "unicodeLigature_ft") );
    menuList->value(MENU_INSERT_LIGATURE)->addAction( getAction( tr("st"),  "", "unicodeLigature_st") );
}

void MenuManager::initInsertMarksMenu()
{
    menuList->value(MENU_INSERT_MARKS)->addAction( getAction( tr("Anchor Mark"),        "", "insertMarkAnchor") );
    menuList->value(MENU_INSERT_MARKS)->addAction( getAction( tr("Foot/Endnote"),       "", "insertMarkNote") );
    menuList->value(MENU_INSERT_MARKS)->addAction( getAction( tr("Reference to Item"),  "", "insertMarkItem") );
    menuList->value(MENU_INSERT_MARKS)->addAction( getAction( tr("Reference to Mark"),  "", "insertMark2Mark") );
    menuList->value(MENU_INSERT_MARKS)->addAction( getAction( tr("Variable Text"),      "", "insertMarkVariableText") );
}


/* ********************************************************************************* *
 *
 * TABLE Menu
 *
 * ********************************************************************************* */

void MenuManager::initTableMenu()
{
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Insert &Rows"),                  "table-insert-row",     "tableInsertRows") );
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Insert &Columns"),               "table-insert-column",  "tableInsertColumns") );
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Delete Ro&ws"),                  "table-delete-row",     "tableDeleteRows") );
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Delete Co&lumns"),               "table-delete-column",  "tableDeleteColumns") );
     menuList->value(MENU_TABLE)->addSeparator();
     menuList->value(MENU_TABLE)->addAction( getAction( tr("&Merge Cells"),                  "table-merge-cells",    "tableMergeCells") );
     menuList->value(MENU_TABLE)->addAction( getAction( tr("&Split Cells"),                  "table-split-cells",    "tableSplitCells") );
     menuList->value(MENU_TABLE)->addSeparator();
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Set Row &Heights"),              "table-row-height",     "tableSetRowHeights") );
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Set Columns &Widths"),           "table-column-width",   "tableSetColumnWidths") );
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Distribute Rows &Evenly"),       "",                     "tableDistributeRowsEvenly") );
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Distribute Columns E&venly"),    "",                     "tableDistributeColumnsEvenly") );
     menuList->value(MENU_TABLE)->addSeparator();
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Adjust &Frame to Table"),        "",                     "tableAdjustFrameToTable") );
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Adjust &Table to Frame"),        "",                     "tableAdjustTableToFrame") );

}

/* ********************************************************************************* *
 *
 * EXTRAS Menu
 *
 * ********************************************************************************* */

void MenuManager::initExtrasMenu()
{
    menuList->value(MENU_EXTRAS)->addAction( getAction( tr("&Hyphenate Text"),              "", "extrasHyphenateText") );
    menuList->value(MENU_EXTRAS)->addAction( getAction( tr("&Dehyphenate Text"),            "", "extrasDeHyphenateText") );
    menuList->value(MENU_EXTRAS)->addAction( getAction( tr("Short &Words"),                 "", "ShortWords") );
    menuList->value(MENU_EXTRAS)->addAction( getAction( tr("Check &Spelling"),              "", "HunspellPlugin") );
    menuList->value(MENU_EXTRAS)->addAction( getAction( tr("Generate &Table of Contents"),  "", "extrasGenerateTableOfContents") );
    menuList->value(MENU_EXTRAS)->addAction( getAction( tr("Update &Marks"),                "", "itemUpdateMarks") );
    menuList->value(MENU_EXTRAS)->addAction( getAction( tr("&Font Preview"),                "", "FontPreview") );
    menuList->value(MENU_EXTRAS)->addSeparator();
    menuList->value(MENU_EXTRAS)->addAction( getAction( tr("&Manage Images"),               "", "extrasManageImages") );
    menuList->value(MENU_EXTRAS)->addAction( getAction( tr("&Picture Browser"),             "", "Picture Browser") );
    menuList->value(MENU_EXTRAS)->addSeparator();
    menuList->value(MENU_EXTRAS)->addAction( getAction( tr("&Update Document"),             "", "extrasUpdateDocument") );

}

/* ********************************************************************************* *
 *
 * VIEW Menu
 *
 * ********************************************************************************* */

void MenuManager::initViewMenu()
{

    QMenu * mViewZoom = new QMenu( tr("&Zoom") );
    QMenu * mViewMeasurement = new QMenu( tr("&Measurement") );
    QMenu * mViewPreview = new QMenu( tr("&Preview") );
    QMenu * mViewTextframes = new QMenu( tr("&Text Frames") );
    QMenu * mViewImageframes = new QMenu( tr("&Image Frames") );
    QMenu * mViewDocument = new QMenu( tr("&Document") );
    QMenu * mViewGridsGuides = new QMenu( tr("&Grids && Guides") );

    menuList->insert(MENU_VIEW_ZOOM, mViewZoom);
    menuList->insert(MENU_VIEW_MEASUREMENT, mViewMeasurement);
    menuList->insert(MENU_VIEW_PREVIEW, mViewPreview);
    menuList->insert(MENU_VIEW_TEXTFRAMES, mViewTextframes);
    menuList->insert(MENU_VIEW_IMAGEFRAMES, mViewImageframes);
    menuList->insert(MENU_VIEW_DOCUMENT, mViewDocument);
    menuList->insert(MENU_VIEW_GRIDSGUIDES, mViewGridsGuides);

    menuList->value(MENU_VIEW)->addMenu( mViewZoom );
    menuList->value(MENU_VIEW)->addMenu( mViewMeasurement );
    menuList->value(MENU_VIEW)->addMenu( mViewPreview );
    menuList->value(MENU_VIEW)->addMenu( mViewTextframes );
    menuList->value(MENU_VIEW)->addMenu( mViewImageframes );
    menuList->value(MENU_VIEW)->addMenu( mViewDocument );
    menuList->value(MENU_VIEW)->addMenu( mViewGridsGuides );

}

void MenuManager::initViewZoomMenu()
{
    menuList->value(MENU_VIEW_ZOOM)->addAction( getAction( tr("Fit to &Height"),    "", "viewFitInWindow") );
    menuList->value(MENU_VIEW_ZOOM)->addAction( getAction( tr("Fit to &Width"),     "", "viewFitWidth") );
    menuList->value(MENU_VIEW_ZOOM)->addAction( getAction( tr("&50%"),              "", "viewFit50") );
    menuList->value(MENU_VIEW_ZOOM)->addAction( getAction( tr("&75%"),              "", "viewFit75") );
    menuList->value(MENU_VIEW_ZOOM)->addAction( getAction( tr("&100%"),             "", "viewFit100") );
    menuList->value(MENU_VIEW_ZOOM)->addAction( getAction( tr("&200%"),             "", "viewFit200") );
    menuList->value(MENU_VIEW_ZOOM)->addAction( getAction( tr("&400%"),             "", "viewFit400") );

}

void MenuManager::initViewPreviewMenu()
{
    menuList->value(MENU_VIEW_PREVIEW)->addAction( getAction( tr("Preview Mode"), "preview-document", "viewPreviewMode") );
}

void MenuManager::initViewMeasurementMenu()
{
    menuList->value(MENU_VIEW_MEASUREMENT)->addAction( getAction( tr("Show &Ruler"),                     "", "viewShowRulers", true) );
    menuList->value(MENU_VIEW_MEASUREMENT)->addAction( getAction( tr("Ruler Relative to &Page"),         "", "", true) );
    menuList->value(MENU_VIEW_MEASUREMENT)->addAction( getAction( tr("Move/Resize Value &Indicator"),    "", "", true) );
}

void MenuManager::initViewTextFramesMenu()
{
    menuList->value(MENU_VIEW_TEXTFRAMES)->addAction( getAction( tr("Show &Baseline Grid"),      "", "viewShowBaseline",         true) );
    menuList->value(MENU_VIEW_TEXTFRAMES)->addAction( getAction( tr("Show Text &Frame Columns"), "", "viewShowColumnBorders",    true) );
    menuList->value(MENU_VIEW_TEXTFRAMES)->addAction( getAction( tr("Show &Text Chain"),         "", "viewShowTextChain",        true) );
    menuList->value(MENU_VIEW_TEXTFRAMES)->addAction( getAction( tr("Show Control &Characters"), "", "viewShowTextControls",     true) );
}

void MenuManager::initViewImageFramesMenu()
{
    menuList->value(MENU_VIEW_IMAGEFRAMES)->addAction( getAction( tr("Show &Images"), "", "viewShowImages", true) );
}

void MenuManager::initViewDocumentMenu()
{
    menuList->value(MENU_VIEW_DOCUMENT)->addAction( getAction( tr("Show &Margins"),          "", "viewShowMargins",      true) );
    menuList->value(MENU_VIEW_DOCUMENT)->addAction( getAction( tr("Show &Bleeds"),           "", "viewShowBleeds",       true) );
    menuList->value(MENU_VIEW_DOCUMENT)->addAction( getAction( tr("Show &Frames"),           "", "viewShowFrames",       true) );
    menuList->value(MENU_VIEW_DOCUMENT)->addAction( getAction( tr("Show &Layer Indicators"), "", "viewShowLayerMarkers", true) );
}

void MenuManager::initViewGridsGuidesMenu()
{
    menuList->value(MENU_VIEW_GRIDSGUIDES)->addAction( getAction( tr("Show &Grid"),     "", "viewShowGrid",     true) );
    menuList->value(MENU_VIEW_GRIDSGUIDES)->addAction( getAction( tr("Show G&uides"),   "", "viewShowGuides",   true) );
}

/* ********************************************************************************* *
 *
 * SCRIPT Menu
 *
 * ********************************************************************************* */

void MenuManager::initScriptMenu()
{
    QMenu * mScriptScribusScripts = new QMenu( tr("&Scribus Scripts") );
    QMenu * mScriptRecentScripts = new QMenu( tr("&Recent Scripts") );

    menuList->insert(MENU_SCRIPT_SCRIBUS, mScriptScribusScripts);
    menuList->insert(MENU_SCRIPT_RECENT, mScriptRecentScripts);

    menuList->value(MENU_SCRIPT)->addMenu(mScriptScribusScripts);
    menuList->value(MENU_SCRIPT)->addMenu(mScriptRecentScripts);
    menuList->value(MENU_SCRIPT)->addAction( getAction( tr("&Execute Script"),  "", "") );
    menuList->value(MENU_SCRIPT)->addSeparator();
    menuList->value(MENU_SCRIPT)->addAction( getAction( tr("Show &Console"),    "", "") );
    menuList->value(MENU_SCRIPT)->addAction( getAction( tr("&About Script"),    "", "") );

}

void MenuManager::initScriptScribusScripts()
{
    menuList->value(MENU_SCRIPT_SCRIBUS)->clear();

    // TODO: add logic to load recent files
}

void MenuManager::initScriptRecentScripts()
{
    menuList->value(MENU_SCRIPT_RECENT)->clear();

    // TODO: add logic to load recent files
}

/* ********************************************************************************* *
 *
 * HELP Menu
 *
 * ********************************************************************************* */

void MenuManager::initHelpMenu()
{
    menuList->value(MENU_HELP)->addAction( getAction( tr("Scribus &Help"),                  "", "helpManual") );
    menuList->value(MENU_HELP)->addAction( getAction( tr("Chat with the Community"),        "", "helpChat") );
    menuList->value(MENU_HELP)->addSeparator();
    menuList->value(MENU_HELP)->addAction( getAction( tr("Action &Search"),                 "", "helpActionSearch") );
    menuList->value(MENU_HELP)->addAction( getAction( tr("&Tooltips"),                      "", "helpTooltips", true) );
    menuList->value(MENU_HELP)->addSeparator();
    menuList->value(MENU_HELP)->addAction( getAction( tr("Scribus &Homepage"),              "", "helpOnlineWWW") );
    menuList->value(MENU_HELP)->addAction( getAction( tr("Scribus Online Documentation"),   "", "helpOnlineDocs") );
    menuList->value(MENU_HELP)->addAction( getAction( tr("Scribus &Wiki"),                  "", "helpOnlineWiki") );
    menuList->value(MENU_HELP)->addAction( getAction( tr("&Getting Started with Scribus"),  "", "helpOnlineTutorial1") );
    menuList->value(MENU_HELP)->addSeparator();
    menuList->value(MENU_HELP)->addAction( getAction( tr("Check for &Updates"),             "", "helpCheckUpdates") );
    menuList->value(MENU_HELP)->addSeparator();
    menuList->value(MENU_HELP)->addAction( getAction( tr("&About Scribus"),                 "", "helpAboutScribus") );
    menuList->value(MENU_HELP)->addAction( getAction( tr("About &Plugins"),                 "", "helpAboutPlugins") );
    menuList->value(MENU_HELP)->addAction( getAction( tr("About &Qt"),                      "", "helpAboutQt") );

}
