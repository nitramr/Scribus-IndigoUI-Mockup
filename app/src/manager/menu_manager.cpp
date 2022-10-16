#include "menu_manager.h"
#include "autoforms_menu/autoforms_menu.h"
#include "block_fill.h"
#include "block_stroke.h"
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
    return menuList->value("window");
}

/* ********************************************************************************* *
 *
 * Private Methods
 *
 * ********************************************************************************* */

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

    // Insert
    initInsertMenu();

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
    menuList->value(MENU_FILE)->addAction( getAction( tr("&Close"),                 "",                 "fileQuit") );
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

/* ********************************************************************************* *
 *
 * TABLE Menu
 *
 * ********************************************************************************* */

void MenuManager::initTableMenu()
{
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Insert Rows"),                  "table-insert-row",     "tableInsertRows") );
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Insert Columns"),               "table-insert-column",  "tableInsertColumns") );
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Delete Rows"),                  "table-delete-row",     "tableDeleteRows") );
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Delete Columns"),               "table-delete-column",  "tableDeleteColumns") );
     menuList->value(MENU_TABLE)->addSeparator();
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Merge Cells"),                  "table-merge-cells",    "tableMergeCells") );
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Split Cells"),                  "table-split-cells",    "tableSplitCells") );
     menuList->value(MENU_TABLE)->addSeparator();
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Set Row Heights"),              "table-row-height",     "tableSetRowHeights") );
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Set Columns Widths"),           "table-column-width",   "tableSetColumnWidths") );
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Distribute Rows Evenly"),       "",                     "tableDistributeRowsEvenly") );
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Distribute Columns Evenly"),    "",                     "tableDistributeColumnsEvenly") );
     menuList->value(MENU_TABLE)->addSeparator();
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Adjust Frame to Table"),        "",                     "tableAdjustFrameToTable") );
     menuList->value(MENU_TABLE)->addAction( getAction( tr("Adjust Table to Frame"),        "",                     "tableAdjustTableToFrame") );

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
