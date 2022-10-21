#include "menu_manager.h"
#include "autoforms_menu/autoforms_menu.h"
#include "mainwindow.h"
#include "icon_manager.h"
#include "shortcut_manager.h"
#include "dock_documentbase.h"

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

QAction *MenuManager::getAction(const QString &label, QString iconKey, QString shortcutKey, ActionType type, bool checked)
{
    IconManager &iconManager = IconManager::instance();

    QAction * action = new QAction(label);

    if(!iconKey.isEmpty())
        action->setIcon( iconManager.icon(iconKey) );

    if(!shortcutKey.isEmpty())
        action->setShortcut( getShortcut(shortcutKey) );

    action->setCheckable(type);
    action->setChecked(checked);

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


void MenuManager::initPageContextMenu(QMenu *menu, DockDocumentBase *documentBase, DummyDocument *document)
{
    menu->addAction( getAction( tr("Paste File"),               "",     "") );
    menu->addSeparator();
    menu->addAction( getAction( tr("&Undo"),                    "undo", "editUndoAction") );
    menu->addAction( getAction( tr("&Redo"),                    "redo", "editRedoAction") );
    menu->addSeparator();
    menu->addAction( getAction( tr("Show Margins"),             "",     "viewShowMargins",          ActionType::Checkbox) );
    menu->addAction( getAction( tr("Show Frames"),              "",     "viewShowFrames",           ActionType::Checkbox) );
    menu->addAction( getAction( tr("Show Layer Indicators"),    "",     "viewShowLayerMarkers",     ActionType::Checkbox) );
    menu->addAction( getAction( tr("Show Images"),              "",     "viewShowImages",           ActionType::Checkbox) );
    menu->addAction( getAction( tr("Show Grid"),                "",     "viewShowGrid",             ActionType::Checkbox, document,         &DummyDocument::toggleGridVisibility) );
    menu->addAction( getAction( tr("Show Guides"),              "",     "viewShowGuides",           ActionType::Checkbox, document,         &DummyDocument::toggleGuideVisibility) );
    menu->addAction( getAction( tr("Show Text Frame Columns"),  "",     "viewShowColumnBorders",    ActionType::Checkbox) );
    menu->addAction( getAction( tr("Show Baseline Grid"),       "",     "viewShowBaseline",         ActionType::Checkbox, document,         &DummyDocument::toggleBaselineVisibility) );
    menu->addAction( getAction( tr("Show Text Chain"),          "",     "viewShowTextChain",        ActionType::Checkbox) );
    menu->addAction( getAction( tr("Show Rulers"),              "",     "viewShowRulers",           ActionType::Checkbox) );
    menu->addAction( getAction( tr("Rulers Relative to Page"),  "",     "",                         ActionType::Checkbox) );
    menu->addSeparator();
    menu->addAction( getAction( tr("Snap to Grid"),             "",     "viewSnapToGrid",           ActionType::Checkbox) );
    menu->addAction( getAction( tr("Snap to Guides"),           "",     "viewSnapToGuides",         ActionType::Checkbox) );
    menu->addAction( getAction( tr("Snap to Items"),            "",     "viewSnapToElements",       ActionType::Checkbox) );
    menu->addSeparator();
    menu->addAction( getAction( tr("Apply Master Page"),        "",     "pageApplyMasterPage") );
    menu->addAction( getAction( tr("Manage Guides"),            "",     "pageManageGuides") );
    menu->addAction( getAction( tr("Manage Page Properties"),   "",     "pageManageProperties",     ActionType::Normal,     documentBase,   &DockDocumentBase::showManagePageDialog) );
    menu->addSeparator();
    menu->addAction( getAction( tr("Delete Page"),              "",     "pageDelete") );

}

void MenuManager::initImageItemContextMenu(QMenu *menu)
{
    QMenu * mPreviewSettings    = new QMenu( tr("&Preview Settings") );
    QMenu * mLocking            = new QMenu( tr("&Locking") );
    QMenu * mSendTo             = new QMenu( tr("&Send to") );
    QMenu * mLevel              = new QMenu( tr("&Level") );
    QMenu * mConvertTo          = new QMenu( tr("&Convert to") );

    initItemImagePreviewSettingsMenu( mPreviewSettings );
    initItemLockingMenu( mLocking );
    initItemSendToMenu( mSendTo );
    initItemLevelMenu( mLevel );
    initItemConvertToMenu( mConvertTo );

    // Info
    // Content
    menu->addSeparator();
    menu->addAction( getAction( tr("Update Marks"),         "", "itemUpdateMarks") );
    menu->addMenu( mPreviewSettings );
    menu->addSeparator();
    menu->addMenu( mLocking );
    menu->addMenu( mSendTo );
    menu->addMenu( mLevel );
    menu->addMenu( mConvertTo );
    menu->addSeparator();
    menu->addAction( getAction( tr("Attributes"),           "", "itemAttributes") );
    menu->addSeparator();
    // Edit
    menu->addSeparator();
    menu->addAction( getAction( tr("Frame Properties"),     "", "toolsProperties") );
    menu->addAction( getAction( tr("Content Properties"),   "", "toolsContent") );

}

void MenuManager::initRootMenu(QMenuBar *menu)
{
    // Root Menu
    QMenu * mFile   = new QMenu( tr("&File") );
    QMenu * mEdit   = new QMenu( tr("&Edit") );
    QMenu * mItem   = new QMenu( tr("&Item") );
    QMenu * mInsert = new QMenu( tr("I&nsert") );
    QMenu * mPage   = new QMenu( tr("&Page") );
    QMenu * mTable  = new QMenu( tr("&Table") );
    QMenu * mExtras = new QMenu( tr("E&xtras") );
    QMenu * mView   = new QMenu( tr("&View") );
    QMenu * mScript = new QMenu( tr("&Script") );
    QMenu * mWindow = new QMenu( tr("&Window") );
    QMenu * mHelp   = new QMenu( tr("&Help") );

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

    initFileMenu( mFile );
    initEditMenu( mEdit );
    initItemMenu( mItem );
    initInsertMenu( mInsert );
    initPageMenu( mPage );
    initTableMenu( mTable );
    initExtrasMenu( mExtras );
    initViewMenu( mView );
    initScriptMenu( mScript );
    initHelpMenu( mHelp );
}

/* ********************************************************************************* *
 *
 * Private Methods
 *
 * ********************************************************************************* */

/* ********************************************************************************* *
 *
 * FILE Menu
 *
 * ********************************************************************************* */

void MenuManager::initFileMenu(QMenu *menu)
{

    QMenu * mFileImport = new QMenu(tr("&Import"));
    QMenu * mFileExport = new QMenu(tr("E&xport"));
    QMenu * mFileOutputPreview = new QMenu(tr("&Output Preview"));
    QMenu * mFileRecentFiles = new QMenu(tr("Open &Recent"));

    menuList->insert(MENU_FILE_IMPORT, mFileImport);
    menuList->insert(MENU_FILE_EXPORT, mFileExport);
    menuList->insert(MENU_FILE_OUTPUTPREVIEW, mFileOutputPreview);
    menuList->insert(MENU_FILE_RECENTFILES, mFileRecentFiles);

    initFileImportMenu( mFileImport );
    initFileExportMenu( mFileExport );
    initFileOutputPreviewMenu( mFileOutputPreview );
    initFileRecentFiles( mFileRecentFiles );

    menu->addAction( getAction( tr("&New Document"),          "file-document",    "fileNew",              ActionType::Normal, mainWindow, &MainWindow::newDocument) );
    menu->addAction( getAction( tr("New from Template"),      "",                 "fileNewFromTemplate") );
    menu->addAction( getAction( tr("&Open Document"),         "open",             "fileOpen",             ActionType::Normal, mainWindow, &MainWindow::openDocument) );
    menu->addMenu( mFileRecentFiles );
    menu->addSeparator();
    menu->addAction( getAction( tr("&Close"),                 "",                 "fileClose") );
    menu->addAction( getAction( tr("&Save"),                  "save",             "fileSave") );
    menu->addAction( getAction( tr("Save &As"),               "save",             "fileSaveAs") );
    menu->addAction( getAction( tr("Save as &Template"),      "",                 "SaveAsDocumentTemplate") );
    menu->addAction( getAction( tr("Re&vert to Saved"),       "",                 "fileRevert") );
    menu->addAction( getAction( tr("Collect from O&utput"),   "",                 "fileCollect") );
    menu->addSeparator();
    menu->addMenu( mFileImport );
    menu->addMenu( mFileExport );
    menu->addSeparator();
    menu->addAction( getAction( tr("&Document Setup"),        "",                 "fileDocSetup150") );
    menu->addAction( getAction( tr("Pre&ferences"),           "",                 "filePreferences150") );
    menu->addSeparator();
    menu->addAction( getAction( tr("&Print"),                 "print",            "filePrint") );
    menu->addAction( getAction( tr("Print Previe&w"),         "",                 "PrintPreview") );
    menu->addSeparator();
    menu->addMenu( mFileOutputPreview );
    menu->addSeparator();
    menu->addAction( getAction( tr("&Quit"),                  "",                 "fileQuit") );


}

void MenuManager::initFileImportMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Get Text"),        "", "fileImportText") );
    menu->addAction( getAction( tr("Append Text"),     "", "fileImportAppendText") );
    menu->addAction( getAction( tr("Get Image"),       "", "fileImportImage") );
    menu->addAction( getAction( tr("Get Vector File"), "", "fileImportVector") );
}

void MenuManager::initFileExportMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Save Text"),       "", "fileExportText") );
    menu->addAction( getAction( tr("Save as EPS"),     "", "fileExportAsEPS") );
    menu->addAction( getAction( tr("Save as PDF"),     "", "fileExportAsPDF") );
    menu->addAction( getAction( tr("Save as Image"),   "", "ExportAsImage") );
    menu->addAction( getAction( tr("Save as SVG"),     "", "ExportAsSVG") );
    menu->addAction( getAction( tr("Save as XPS"),     "", "ExportAsXPS") );
}

void MenuManager::initFileOutputPreviewMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("PDF"),          "", "OutputPreviewPDF") );
    menu->addAction( getAction( tr("Postscript"),   "", "OutputPreviewPS") );
}

void MenuManager::initFileRecentFiles(QMenu *menu)
{
    menu->clear();

    // TODO: add logic to load recent files

}

/* ********************************************************************************* *
 *
 * EDIT Menu
 *
 * ********************************************************************************* */

void MenuManager::initEditMenu(QMenu *menu)
{

    QMenu * mEditContents = new QMenu( tr("Contents") );

    menuList->insert(MENU_EDIT_CONTENTS, mEditContents);

    initEditContentsMenu(mEditContents);

    menu->addAction( getAction( tr("&Undo"),                  "undo",     "editUndoAction") );
    menu->addAction( getAction( tr("&Redo"),                  "redo",     "editRedoAction") );
    menu->addAction( getAction( tr("&Item Action Mode"),      "",         "", ActionType::Checkbox) );
    menu->addSeparator();
    menu->addAction( getAction( tr("Cu&t"),                   "cut",      "editCut") );
    menu->addAction( getAction( tr("&Copy"),                  "copy",     "editCopy") );
    menu->addAction( getAction( tr("&Paste"),                 "paste",    "editPaste") );
    menu->addAction( getAction( tr("&Delete"),                "delete",   "itemDelete") );
    menu->addMenu( mEditContents );
    menu->addSeparator();
    menu->addAction( getAction( tr("Select &All"),            "",         "editSelectAll") );
    menu->addAction( getAction( tr("Advanced Select All"),    "",         "editSelectAllOnLayer") );
    menu->addAction( getAction( tr("&Deselect &All"),         "",         "editDeselectAll") );
    menu->addSeparator();
    menu->addAction( getAction( tr("&Search/Replace"),        "search",   "editSearchReplace") );
    menu->addAction( getAction( tr("Edit Image"),             "", "") );
    menu->addAction( getAction( tr("Edit Source"),            "", "") );
    menu->addSeparator();
    menu->addAction( getAction( tr("Colors && Fills"),        "",         "editColorsAndFills") );
    menu->addAction( getAction( tr("Replace Colors"),         "",         "editReplaceColors") );
    menu->addAction( getAction( tr("Styles"),                 "",         "editStyles", ActionType::Normal, mainWindow, &MainWindow::openStyles) );
    menu->addAction( getAction( tr("Marks"),                  "",         "editMarks") );
    menu->addAction( getAction( tr("Parent Pages"),           "",         "editMasterPages") );
    menu->addAction( getAction( tr("Javascript"),             "",         "editJavascripts") );


}

void MenuManager::initEditContentsMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Cu&t"),              "cut",      "editCut") );
    menu->addAction( getAction( tr("&Copy"),             "copy",     "editCopyContents") );
    menu->addAction( getAction( tr("&Paste"),            "paste",    "editPasteContents") );
    menu->addAction( getAction( tr("Paste (&Absolute)"), "paste",    "editPasteContentsAbs") );
    menu->addAction( getAction( tr("&Delete"),           "delete",   "editClearContents") );
    menu->addAction( getAction( tr("T&runcate"),         "",         "editTruncateContents") );
}

/* ********************************************************************************* *
 *
 * PAGE Menu
 *
 * ********************************************************************************* */

void MenuManager::initPageMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("&Insert"),                    "", "pageInsert") );
    menu->addAction( getAction( tr("Imp&ort"),                    "", "pageImport") );
    menu->addAction( getAction( tr("&Delete"),                    "", "pageDelete") );
    menu->addAction( getAction( tr("&Copy"),                      "", "pageCopy") );
    menu->addAction( getAction( tr("&Move"),                      "", "pageMove") );
    menu->addSeparator();
    menu->addAction( getAction( tr("&Apply Parent Page"),         "", "pageApplyMasterPage") );
    menu->addAction( getAction( tr("Con&vert to Parent Page"),    "", "pageCopyToMasterPage") );
    menu->addAction( getAction( tr("Manage &Guides"),             "", "pageManageGuides") );
    menu->addAction( getAction( tr("Manage Page &Properties"),    "", "pageManageProperties") );
    menu->addSeparator();
    menu->addAction( getAction( tr("Snap to G&rid"),              "", "viewSnapToGrid", ActionType::Checkbox) );
    menu->addAction( getAction( tr("Snap to G&uides"),            "", "viewSnapToGuides", ActionType::Checkbox) );
    menu->addAction( getAction( tr("Snap to It&ems"),             "", "viewSnapToElements", ActionType::Checkbox) );

}

/* ********************************************************************************* *
 *
 * ITEM Menu
 *
 * ********************************************************************************* */

void MenuManager::initItemMenu(QMenu *menu)
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

    initItemDuplicateTransformMenu( mItemDuplicateTransform );
    initItemGroupingMenu(mItemGrouping );
    initItemLockingMenu(  mItemLocking );
    initItemLevelMenu( mItemLevel );
    initItemSendToLayerMenu( mItemSendToLayer );
    initItemSendToMenu( mItemSendTo );
    initItemAdjustMenu( mItemAdjust );
    initItemImageMenu( mItemImage );
    initItemPDFOptionsMenu( mItemPDFOptions );
    initItemConvertToMenu( mItemConvertTo );
    initItemTextFrameLinksMenu( mItemTextFrameLinks );
    initItemPathToolsMenu( mItemPathTool );
    initItemWeldingMenu( mItemWelding );
    initItemMarksMenu( mItemMarks );
    initItemTextFeaturesMenu( mItemTextFeatures );

    menu->addMenu( mItemDuplicateTransform );
    menu->addMenu( mItemGrouping );
    menu->addMenu( mItemLocking );
    menu->addMenu( mItemLevel );
    menu->addMenu( mItemSendToLayer );
    menu->addMenu( mItemSendTo );
    menu->addMenu( mItemAdjust );
    menu->addMenu( mItemImage );
    menu->addMenu( mItemPDFOptions );
    menu->addMenu( mItemConvertTo );
    menu->addMenu( mItemTextFrameLinks );
    menu->addMenu( mItemPathTool );
    menu->addMenu( mItemWelding );
    menu->addMenu( mItemMarks );
    menu->addMenu( mItemTextFeatures );

}

void MenuManager::initItemDuplicateTransformMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("&Duplicate"),           "", "itemDuplicate") );
    menu->addAction( getAction( tr("&Multiple Duplicate"),  "", "itemMulDuplicate") );
    menu->addAction( getAction( tr("&Transform"),           "", "itemTransform") );
}

void MenuManager::initItemGroupingMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("&Group"),        "", "itemGroup") );
    menu->addAction( getAction( tr("&Ungroup"),      "", "itemUngroup") );
    menu->addAction( getAction( tr("&Adjust Group"), "", "itemGroupAdjust") );
}

void MenuManager::initItemLockingMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Is &Locked"),      "", "itemLock",     ActionType::Checkbox) );
    menu->addAction( getAction( tr("&Size is Locked"), "", "itemLockSize", ActionType::Checkbox) );
}

void MenuManager::initItemLevelMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("To &Foreground"),    "level-foreground", "itemRaiseToTop") );
    menu->addAction( getAction( tr("&Raise"),            "level-up",         "itemRaise") );
    menu->addAction( getAction( tr("&Lower"),            "level-down",       "itemLower") );
    menu->addAction( getAction( tr("To &Background"),    "level-background", "itemLowerToBottom") );
}

void MenuManager::initItemSendToLayerMenu(QMenu *menu)
{
    menu->clear();
    menu->addAction( getAction( tr("Background"), "", "") );

    // TODO: add logic to load recent files
}

void MenuManager::initItemSendToMenu(QMenu *menu)
{
    QMenu * mItemSendToScrapbook = new QMenu(tr("&Scrapbook"));

    menuList->insert(MENU_ITEM_SENDTO_SCRAPBOOK, mItemSendToScrapbook);

    initItemSendToScrapbookMenu(mItemSendToScrapbook);

    menu->addMenu( mItemSendToScrapbook );
    menu->addAction( getAction( tr("&Patterns"),        "", "itemSendToPattern") );
    menu->addAction( getAction( tr("&Inline-Items"),    "", "itemSendToInline") );
}

void MenuManager::initItemSendToScrapbookMenu(QMenu *menu)
{
    menu->clear();
    // TODO: add logic to load scrapbook files
}

void MenuManager::initItemAdjustMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Adjust Frame &Height to Text"), "", "itemAdjustFrameHeightToText") );
    menu->addAction( getAction( tr("Adjust &Frame to Image"),       "", "itemAdjustFrameToImage") );
    menu->addAction( getAction( tr("Adjust &Image to Frame"),       "", "itemAdjustImageToFrame") );
}

void MenuManager::initItemImageMenu(QMenu *menu)
{
    QMenu * mItemImagePreviewSettings = new QMenu(tr("Preview &Settings"));

    menuList->insert(MENU_ITEM_IMAGE_PREVIEWSETTINGS, mItemImagePreviewSettings);

    initItemImagePreviewSettingsMenu(mItemImagePreviewSettings);

    menu->addAction( getAction( tr("&Update Image"),                "", "itemUpdateImage") );
    menu->addAction( getAction( tr("Extended Image &Properties"),   "", "itemExtendedImageProperties") );
    menu->addAction( getAction( tr("&Embed Image"),                 "", "", ActionType::Checkbox) );
    menu->addMenu( mItemImagePreviewSettings );
}

void MenuManager::initItemImagePreviewSettingsMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Image &Visible"),       "", "itemImageIsVisible", ActionType::Checkbox) );
    menu->addSeparator();
    menu->addAction( getAction( tr("&Full Resolution"),     "", "itemPreviewFull") );
    menu->addAction( getAction( tr("&Normal Resolution"),   "", "itemPreviewNormal") );
    menu->addAction( getAction( tr("&Low Resolution"),      "", "itemPreviewLow") );
}

void MenuManager::initItemPDFOptionsMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Is PDF &Annotation"),       "", "itemPDFIsAnnotation",     ActionType::Checkbox) );
    menu->addAction( getAction( tr("Is PDF &Bookmark"),         "", "itemPDFIsBookmark",       ActionType::Checkbox) );
    menu->addAction( getAction( tr("A&nnotation Properties"),   "", "itemPDFAnnotationProps") );
    menu->addAction( getAction( tr("&Field Properties"),        "", "itemPDFFieldProps") );
}

void MenuManager::initItemConvertToMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("&Text Frame"),   "", "itemConvertToTextFrame") );
    menu->addAction( getAction( tr("&Image Frame"),  "", "itemConvertToImageFrame") );
    menu->addAction( getAction( tr("&Polygon"),      "", "itemConvertToPolygon") );
    menu->addAction( getAction( tr("&Bezier Curve"), "", "itemConvertToBezierCurve") );
    menu->addAction( getAction( tr("&Outlines"),     "", "itemConvertToOutlines") );
    menu->addAction( getAction( tr("&Symbol"),       "", "itemConvertToSymbolFrame") );
}

void MenuManager::initItemTextFrameLinksMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("&Link Text Frame"),                "tool-text-link",   "toolsLinkTextFrame") );
    menu->addAction( getAction( tr("&Unlink Text Frame"),              "tool-text-unlink", "toolsUnlinkTextFrame") );
    menu->addAction( getAction( tr("Unlink Text Frame and &Cut Text"), "",                 "toolsUnlinkTextFrameAndCutText") );
}

void MenuManager::initItemPathToolsMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("&Combine Polygons"),         "", "itemCombinePolygons") );
    menu->addAction( getAction( tr("&Split Polygons"),           "", "itemSplitPolygons") );
    menu->addAction( getAction( tr("&Attach Text to Path"),      "", "itemAttachTextToPath") );
    menu->addAction( getAction( tr("&Detach Text from Path"),    "", "itemDetachTextFromPath") );
    menu->addAction( getAction( tr("&Flatten Path"),             "", "FlattenPath") );
    menu->addAction( getAction( tr("&Lens Effects"),             "", "LensEffects") );
    menu->addAction( getAction( tr("&Mesh Distortion"),          "", "MeshDistortion") );
    menu->addAction( getAction( tr("&Path along Path"),          "", "PathAlongPath") );
    menu->addAction( getAction( tr("C&onnect Paths"),            "", "PathConnect") );
    menu->addAction( getAction( tr("C&ut Polygon"),              "", "PathCutter") );
    menu->addAction( getAction( tr("P&ath Operations"),          "", "") );
    menu->addAction( getAction( tr("C&reate Path from Stroke"),  "", "PathStroker") );
    menu->addAction( getAction( tr("Smoo&th Path"),              "", "SmoothPath") );
    menu->addAction( getAction( tr("Su&bdivide Path"),           "", "Subdivide") );
}

void MenuManager::initItemWeldingMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("&Weld Items"),    "", "itemWeld") );
    menu->addAction( getAction( tr("&Unweld Items"),  "", "itemsUnWeld") );
    menu->addAction( getAction( tr("&Edit Weld"),     "", "itemEditWeld") );
}

void MenuManager::initItemMarksMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("&Edit Mark"), "", "editMark") );
}

void MenuManager::initItemTextFeaturesMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("&Left"),               "text-align-left",              "alignLeft") );
    menu->addAction( getAction( tr("&Center"),             "text-align-center",            "alignCenter") );
    menu->addAction( getAction( tr("&Right"),              "text-align-right",             "alignRight") );
    menu->addAction( getAction( tr("&Block"),              "text-align-justified",         "alignBlock") );
    menu->addAction( getAction( tr("&Forced"),             "text-align-forcedjustified",   "alignForced") );
    menu->addSeparator();
    menu->addAction( getAction( tr("&Normal"),             "",                             "typeEffectNormal") );
    menu->addAction( getAction( tr("&Underline"),          "text-format-underline",        "typeEffectUnderline") );
    menu->addAction( getAction( tr("Underline &Words"),    "",                             "typeEffectUnderlineWords") );
    menu->addAction( getAction( tr("&Strike Through"),     "text-format-strikeout",        "typeEffectStrikeThrough") );
    menu->addAction( getAction( tr("&All Caps"),           "",                             "typeEffectAllCaps") );
    menu->addAction( getAction( tr("S&mall Caps"),         "",                             "typeEffectSmallCaps") );
    menu->addAction( getAction( tr("Su&perscript"),        "text-format-superscript",      "typeEffectSuperscript") );
    menu->addAction( getAction( tr("Subscr&ipt"),          "text-format-subscript",        "typeEffectSubscript") );
    menu->addAction( getAction( tr("&Outline"),            "text-format-outline",          "typeEffectOutline") );
//    menu->addAction( getAction( tr("Shadow"),           "",                             "typeEffectShadow") );
}

/* ********************************************************************************* *
 *
 * INSERT Menu
 *
 * ********************************************************************************* */

void MenuManager::initInsertMenu(QMenu *menu)
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

    initInsertCharacterMenu(mInsertCharacter);
    initInsertQuoteMenu(mInsertQuote);
    initInsertSpacesBreaksMenu(mInsertSpacesBreaks);
    initInsertLigatureMenu(mInsertLigature);
    initInsertMarksMenu(mInsertMarks);

    menu->addAction( getAction( tr("Fra&mes"),              "",                     "") );
    menu->addSeparator();
    menu->addAction( getAction( tr("&Text Frame"),          "tool-text-frame",      "toolsInsertTextFrame") );
    menu->addAction( getAction( tr("&Image Frame"),         "tool-image",           "toolsInsertImageFrame") );
    menu->addAction( getAction( tr("&Render Frame"),        "tool-render-frame",    "toolsInsertRenderFrame") );
    menu->addAction( getAction( tr("Tabl&e"),               "tool-table",           "toolsInsertTable") );
    QAction *actionShape = menu->addMenu(mInsertShape);
    actionShape->setShortcut( getShortcut("toolsInsertShape") );
    menu->addAction( getAction( tr("&Polygon"),             "tool-star",            "toolsInsertPolygon") );
    menu->addAction( getAction( tr("&Arc"),                 "tool-arc",             "toolsInsertArc") );
    menu->addAction( getAction( tr("Sprial"),               "tool-spiral",          "toolsInsertSpiral") );
    menu->addAction( getAction( tr("&Line"),                "tool-line",            "toolsInsertLine") );
    menu->addAction( getAction( tr("&Bezier Curve"),        "tool-bezier",          "toolsInsertBezier") );
    menu->addAction( getAction( tr("&Freehand Line"),       "tool-pencil",          "toolsInsertFreehandLine") );
    menu->addAction( getAction( tr("&Calligraphic Line"),   "tool-calligraphy",     "toolsInsertCalligraphicLine") );
    menu->addAction( getAction( tr("Barco&de"),             "tool-barcode",         "") );
    menu->addSeparator();
    menu->addAction( getAction( tr("Stic&ky Tools"),        "",                     "", ActionType::Checkbox) );
    menu->addSeparator();
    menu->addAction( getAction( tr("Gl&yphs"),              "",                     "") );
    menu->addMenu(mInsertCharacter);
    menu->addMenu(mInsertQuote);
    menu->addMenu(mInsertSpacesBreaks);
    menu->addMenu(mInsertLigature);
    menu->addSeparator();
    menu->addAction( getAction( tr("Sample Te&xt"),         "",                     "") );
    menu->addMenu(mInsertMarks);
}

void MenuManager::initInsertCharacterMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Page &Number"),           "", "unicodePageNumber") );
    menu->addAction( getAction( tr("Number of &Pages"),       "", "unicodePageCount") );
    menu->addAction( getAction( tr("Soft &Hyphen"),           "", "unicodeSoftHyphen") );
    menu->addAction( getAction( tr("Non &Breaking Hyphen"),   "", "unicodeNonBreakingHyphen") );
    menu->addAction( getAction( tr("Zero Width &Joiner"),     "", "unicodeZWJ") );
    menu->addAction( getAction( tr("Zero &Width Non-Joiner"), "", "unicodeZWNJ") );
    menu->addSeparator();
    menu->addAction( getAction( tr("&Copyright"),             "", "unicodeCopyRight") );
    menu->addAction( getAction( tr("&Registered Trademark"),  "", "unicodeRegdTM") );
    menu->addAction( getAction( tr("&Trademark"),             "", "unicodeTM") );
    menu->addAction( getAction( tr("&Solidus"),               "", "unicodeSolidus") );
    menu->addAction( getAction( tr("&Bullet"),                "", "unicodeBullet") );
    menu->addAction( getAction( tr("&Middle Dot"),            "", "unicodeMidpoint") );
    menu->addSeparator();
    menu->addAction( getAction( tr("Em &Dash"),               "", "unicodeDashEm") );
    menu->addAction( getAction( tr("&En Dash"),               "", "unicodeDashEn") );
    menu->addAction( getAction( tr("&Figure Dash"),           "", "unicodeDashFigure") );
    menu->addAction( getAction( tr("&Quotation Dash"),        "", "unicodeDashQuotation") );
}

void MenuManager::initInsertQuoteMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Apostrophe"),             "", "unicodeQuoteApostrophe") );
    menu->addAction( getAction( tr("Straight Double"),        "", "unicodeQuoteStraight") );
    menu->addSeparator();
    menu->addAction( getAction( tr("Single Left"),            "", "unicodeQuoteSingleLeft") );
    menu->addAction( getAction( tr("Single Right"),           "", "unicodeQuoteSingleRight") );
    menu->addAction( getAction( tr("Double Left"),            "", "unicodeQuoteDoubleLeft") );
    menu->addAction( getAction( tr("Double Right"),           "", "unicodeQuoteDoubleRight") );
    menu->addSeparator();
    menu->addAction( getAction( tr("Single Reverse"),         "", "unicodeQuoteSingleReversed") );
    menu->addAction( getAction( tr("Double Reverse"),         "", "unicodeQuoteDoubleReversed") );
    menu->addSeparator();
    menu->addAction( getAction( tr("Low Single Comma"),       "", "unicodeQuoteLowSingleComma") );
    menu->addAction( getAction( tr("Low Double Comma"),       "", "unicodeQuoteLowDoubleComma") );
    menu->addSeparator();
    menu->addAction( getAction( tr("Single Left Guillemet"),  "", "unicodeQuoteSingleLeftGuillemet") );
    menu->addAction( getAction( tr("Single Right Guillemet"), "", "unicodeQuoteSingleRightGuillemet") );
    menu->addAction( getAction( tr("Double Left Guillemet"),  "", "unicodeQuoteDoubleLeftGuillemet") );
    menu->addAction( getAction( tr("Double Right Guillemet"), "", "unicodeQuoteDoubleRightGuillemet") );
    menu->addSeparator();
    menu->addAction( getAction( tr("CJK Single Left"),        "", "unicodeQuoteCJKSingleLeft") );
    menu->addAction( getAction( tr("CJK Single Right"),       "", "unicodeQuoteCJKSingleRight") );
    menu->addAction( getAction( tr("CJK Double Left"),        "", "unicodeQuoteCJKDoubleLeft") );
    menu->addAction( getAction( tr("CJK Double Right"),       "", "unicodeQuoteCJKDoubleRight") );

}

void MenuManager::initInsertSpacesBreaksMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Non &Breaking Space"),      "", "unicodeNonBreakingSpace") );
    menu->addAction( getAction( tr("Narrow No-Break &Space"),   "", "unicodeNarrowNoBreakSpace") );
    menu->addAction( getAction( tr("E&m Space"),                "", "unicodeSpaceEM") );
    menu->addAction( getAction( tr("E&n Space"),                "", "unicodeSpaceEN") );
    menu->addAction( getAction( tr("&Thin Space"),              "", "unicodeSpaceThin") );
    menu->addAction( getAction( tr("Thick Space"),             "", "unicodeSpaceThick") );
    menu->addAction( getAction( tr("&Mid Space"),               "", "unicodeSpaceMid") );
    menu->addAction( getAction( tr("&Hair Space"),              "", "unicodeSpaceHair") );
    menu->addSeparator();
    menu->addAction( getAction( tr("&Zero Width Space"),        "", "unicodeZerowidthSpace") );
    menu->addAction( getAction( tr("Ne&w Line"),                "", "unicodeNewLine") );
    menu->addAction( getAction( tr("&Column Break"),            "", "unicodeColumnBreak") );
    menu->addAction( getAction( tr("&Frame Break"),             "", "unicodeFrameBreak") );

}

void MenuManager::initInsertLigatureMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("ff"),  "", "unicodeLigature_ff") );
    menu->addAction( getAction( tr("fi"),  "", "unicodeLigature_fi") );
    menu->addAction( getAction( tr("fl"),  "", "unicodeLigature_fl") );
    menu->addAction( getAction( tr("ffi"), "", "unicodeLigature_ffi") );
    menu->addAction( getAction( tr("ffl"), "", "unicodeLigature_ffl") );
    menu->addAction( getAction( tr("ft"),  "", "unicodeLigature_ft") );
    menu->addAction( getAction( tr("st"),  "", "unicodeLigature_st") );
}

void MenuManager::initInsertMarksMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Anchor Mark"),        "", "insertMarkAnchor") );
    menu->addAction( getAction( tr("Foot/Endnote"),       "", "insertMarkNote") );
    menu->addAction( getAction( tr("Reference to Item"),  "", "insertMarkItem") );
    menu->addAction( getAction( tr("Reference to Mark"),  "", "insertMark2Mark") );
    menu->addAction( getAction( tr("Variable Text"),      "", "insertMarkVariableText") );
}


/* ********************************************************************************* *
 *
 * TABLE Menu
 *
 * ********************************************************************************* */

void MenuManager::initTableMenu(QMenu *menu)
{
     menu->addAction( getAction( tr("Insert &Rows"),                  "table-insert-row",     "tableInsertRows") );
     menu->addAction( getAction( tr("Insert &Columns"),               "table-insert-column",  "tableInsertColumns") );
     menu->addAction( getAction( tr("Delete Ro&ws"),                  "table-delete-row",     "tableDeleteRows") );
     menu->addAction( getAction( tr("Delete Co&lumns"),               "table-delete-column",  "tableDeleteColumns") );
     menu->addSeparator();
     menu->addAction( getAction( tr("&Merge Cells"),                  "table-merge-cells",    "tableMergeCells") );
     menu->addAction( getAction( tr("&Split Cells"),                  "table-split-cells",    "tableSplitCells") );
     menu->addSeparator();
     menu->addAction( getAction( tr("Set Row &Heights"),              "table-row-height",     "tableSetRowHeights") );
     menu->addAction( getAction( tr("Set Columns &Widths"),           "table-column-width",   "tableSetColumnWidths") );
     menu->addAction( getAction( tr("Distribute Rows &Evenly"),       "",                     "tableDistributeRowsEvenly") );
     menu->addAction( getAction( tr("Distribute Columns E&venly"),    "",                     "tableDistributeColumnsEvenly") );
     menu->addSeparator();
     menu->addAction( getAction( tr("Adjust &Frame to Table"),        "",                     "tableAdjustFrameToTable") );
     menu->addAction( getAction( tr("Adjust &Table to Frame"),        "",                     "tableAdjustTableToFrame") );

}

/* ********************************************************************************* *
 *
 * EXTRAS Menu
 *
 * ********************************************************************************* */

void MenuManager::initExtrasMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("&Hyphenate Text"),              "", "extrasHyphenateText") );
    menu->addAction( getAction( tr("&Dehyphenate Text"),            "", "extrasDeHyphenateText") );
    menu->addAction( getAction( tr("Short &Words"),                 "", "ShortWords") );
    menu->addAction( getAction( tr("Check &Spelling"),              "", "HunspellPlugin") );
    menu->addAction( getAction( tr("Generate &Table of Contents"),  "", "extrasGenerateTableOfContents") );
    menu->addAction( getAction( tr("Update &Marks"),                "", "itemUpdateMarks") );
    menu->addAction( getAction( tr("&Font Preview"),                "", "FontPreview") );
    menu->addSeparator();
    menu->addAction( getAction( tr("&Manage Images"),               "", "extrasManageImages") );
    menu->addAction( getAction( tr("&Picture Browser"),             "", "Picture Browser") );
    menu->addSeparator();
    menu->addAction( getAction( tr("&Update Document"),             "", "extrasUpdateDocument") );

}

/* ********************************************************************************* *
 *
 * VIEW Menu
 *
 * ********************************************************************************* */

void MenuManager::initViewMenu(QMenu *menu)
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

    initViewZoomMenu( mViewZoom );
    initViewPreviewMenu( mViewPreview );
    initViewMeasurementMenu( mViewMeasurement );
    initViewTextFramesMenu( mViewTextframes );
    initViewImageFramesMenu( mViewImageframes );
    initViewDocumentMenu( mViewDocument );
    initViewGridsGuidesMenu( mViewGridsGuides );

    menu->addMenu( mViewZoom );
    menu->addMenu( mViewMeasurement );
    menu->addMenu( mViewPreview );
    menu->addMenu( mViewTextframes );
    menu->addMenu( mViewImageframes );
    menu->addMenu( mViewDocument );
    menu->addMenu( mViewGridsGuides );

}

void MenuManager::initViewZoomMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Fit to &Height"),    "", "viewFitInWindow") );
    menu->addAction( getAction( tr("Fit to &Width"),     "", "viewFitWidth") );
    menu->addAction( getAction( tr("&50%"),              "", "viewFit50") );
    menu->addAction( getAction( tr("&75%"),              "", "viewFit75") );
    menu->addAction( getAction( tr("&100%"),             "", "viewFit100") );
    menu->addAction( getAction( tr("&200%"),             "", "viewFit200") );
    menu->addAction( getAction( tr("&400%"),             "", "viewFit400") );

}

void MenuManager::initViewPreviewMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Preview Mode"), "preview-document", "viewPreviewMode") );
}

void MenuManager::initViewMeasurementMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Show &Ruler"),                     "", "viewShowRulers",  ActionType::Checkbox) );
    menu->addAction( getAction( tr("Ruler Relative to &Page"),         "", "",                ActionType::Checkbox) );
    menu->addAction( getAction( tr("Move/Resize Value &Indicator"),    "", "",                ActionType::Checkbox) );
}

void MenuManager::initViewTextFramesMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Show &Baseline Grid"),      "", "viewShowBaseline",         ActionType::Checkbox) );
    menu->addAction( getAction( tr("Show Text &Frame Columns"), "", "viewShowColumnBorders",    ActionType::Checkbox) );
    menu->addAction( getAction( tr("Show &Text Chain"),         "", "viewShowTextChain",        ActionType::Checkbox) );
    menu->addAction( getAction( tr("Show Control &Characters"), "", "viewShowTextControls",     ActionType::Checkbox) );
}

void MenuManager::initViewImageFramesMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Show &Images"), "", "viewShowImages", ActionType::Checkbox) );
}

void MenuManager::initViewDocumentMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Show &Margins"),          "", "viewShowMargins",      ActionType::Checkbox) );
    menu->addAction( getAction( tr("Show &Bleeds"),           "", "viewShowBleeds",       ActionType::Checkbox) );
    menu->addAction( getAction( tr("Show &Frames"),           "", "viewShowFrames",       ActionType::Checkbox) );
    menu->addAction( getAction( tr("Show &Layer Indicators"), "", "viewShowLayerMarkers", ActionType::Checkbox) );
}

void MenuManager::initViewGridsGuidesMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Show &Grid"),     "", "viewShowGrid",     ActionType::Checkbox) );
    menu->addAction( getAction( tr("Show G&uides"),   "", "viewShowGuides",   ActionType::Checkbox) );
}

/* ********************************************************************************* *
 *
 * SCRIPT Menu
 *
 * ********************************************************************************* */

void MenuManager::initScriptMenu(QMenu *menu)
{
    QMenu * mScriptScribusScripts = new QMenu( tr("&Scribus Scripts") );
    QMenu * mScriptRecentScripts = new QMenu( tr("&Recent Scripts") );

    menuList->insert(MENU_SCRIPT_SCRIBUS, mScriptScribusScripts);
    menuList->insert(MENU_SCRIPT_RECENT, mScriptRecentScripts);

    initScriptScribusScripts( mScriptScribusScripts );
    initScriptRecentScripts( mScriptRecentScripts );

    menu->addMenu(mScriptScribusScripts);
    menu->addMenu(mScriptRecentScripts);
    menu->addAction( getAction( tr("&Execute Script"),  "", "") );
    menu->addSeparator();
    menu->addAction( getAction( tr("Show &Console"),    "", "") );
    menu->addAction( getAction( tr("&About Script"),    "", "") );

}

void MenuManager::initScriptScribusScripts(QMenu *menu)
{
    menu->clear();

    // TODO: add logic to load recent files
}

void MenuManager::initScriptRecentScripts(QMenu *menu)
{
    menu->clear();

    // TODO: add logic to load recent files
}

/* ********************************************************************************* *
 *
 * HELP Menu
 *
 * ********************************************************************************* */

void MenuManager::initHelpMenu(QMenu *menu)
{
    menu->addAction( getAction( tr("Scribus &Help"),                  "", "helpManual") );
    menu->addAction( getAction( tr("Chat with the Community"),        "", "helpChat") );
    menu->addSeparator();
    menu->addAction( getAction( tr("Action &Search"),                 "", "helpActionSearch") );
    menu->addAction( getAction( tr("&Tooltips"),                      "", "helpTooltips",     ActionType::Checkbox) );
    menu->addSeparator();
    menu->addAction( getAction( tr("Scribus &Homepage"),              "", "helpOnlineWWW") );
    menu->addAction( getAction( tr("Scribus Online Documentation"),   "", "helpOnlineDocs") );
    menu->addAction( getAction( tr("Scribus &Wiki"),                  "", "helpOnlineWiki") );
    menu->addAction( getAction( tr("&Getting Started with Scribus"),  "", "helpOnlineTutorial1") );
    menu->addSeparator();
    menu->addAction( getAction( tr("Check for &Updates"),             "", "helpCheckUpdates") );
    menu->addSeparator();
    menu->addAction( getAction( tr("&About Scribus"),                 "", "helpAboutScribus") );
    menu->addAction( getAction( tr("About &Plugins"),                 "", "helpAboutPlugins") );
    menu->addAction( getAction( tr("About &Qt"),                      "", "helpAboutQt") );

}
