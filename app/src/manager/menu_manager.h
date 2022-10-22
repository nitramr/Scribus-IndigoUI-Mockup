#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include <QMenu>
#include <QMenuBar>
#include <QPointer>
#include <QToolBar>

class MainWindow;
class DummyDocument;

class MenuManager : public QObject
{

    Q_OBJECT

public:

    //ActionManager(QMenuBar *menu, MainWindow *mainWindow);
    MenuManager(MenuManager const&) = delete;
    void operator=(MenuManager const&) = delete;
    static MenuManager& instance();

    void setup(MainWindow *window);

    QMenu *menuWindow();

    void initRootMenu(QMenuBar *menu);

    void initDocumentContextMenu(QMenu *menu, DummyDocument *document);
    void initPageContextMenu(QMenu *menu, DummyDocument *document);
    void initImageItemContextMenu(QMenu *menu);


private:

    enum ActionType {
        Normal = 0,
        Checkbox = 1
    };

    const QString MENU_FILE = QStringLiteral("file");
    const QString MENU_FILE_IMPORT = QStringLiteral("file-import");
    const QString MENU_FILE_EXPORT = QStringLiteral("file-export");
    const QString MENU_FILE_OUTPUTPREVIEW = QStringLiteral("file-outputpreview");
    const QString MENU_FILE_RECENTFILES = QStringLiteral("file-recentfiles");
    const QString MENU_EDIT = QStringLiteral("edit");
    const QString MENU_EDIT_CONTENTS = QStringLiteral("edit-contents");
    const QString MENU_ITEM = QStringLiteral("item");
    const QString MENU_ITEM_DUPLICATETRANSFORM = QStringLiteral("item-duplicatetransform");
    const QString MENU_ITEM_GROUPING = QStringLiteral("item-grouping");
    const QString MENU_ITEM_LOCKING = QStringLiteral("item-locking");
    const QString MENU_ITEM_LEVEL = QStringLiteral("item-level");
    const QString MENU_ITEM_SENDTOLAYER = QStringLiteral("item-sendtolayer");
    const QString MENU_ITEM_SENDTO = QStringLiteral("item-sendto");
    const QString MENU_ITEM_SENDTO_SCRAPBOOK = QStringLiteral("item-sendto-scrapbook");
    const QString MENU_ITEM_ADJUST = QStringLiteral("item-adjust");
    const QString MENU_ITEM_IMAGE = QStringLiteral("item-image");
    const QString MENU_ITEM_IMAGE_PREVIEWSETTINGS = QStringLiteral("item-image-previewsettings");
    const QString MENU_ITEM_PDFOPTIONS = QStringLiteral("item-pdfoptions");
    const QString MENU_ITEM_CONVERTTO = QStringLiteral("item-convertto");
    const QString MENU_ITEM_TEXTFRAMELINKS = QStringLiteral("item-textframelinks");
    const QString MENU_ITEM_PATHTOOLS = QStringLiteral("item-pathtools");
    const QString MENU_ITEM_WELDING = QStringLiteral("item-welding");
    const QString MENU_ITEM_MARKS = QStringLiteral("item-marks");
    const QString MENU_ITEM_TEXTFEATURE = QStringLiteral("item-textfeatures");
    const QString MENU_INSERT = QStringLiteral("insert");
    const QString MENU_INSERT_SHAPE = QStringLiteral("insert-shape");
    const QString MENU_INSERT_CHARACTER = QStringLiteral("insert-character");
    const QString MENU_INSERT_QUOTE = QStringLiteral("insert-quote");
    const QString MENU_INSERT_SPACESBREAKS = QStringLiteral("insert-spacesbreaks");
    const QString MENU_INSERT_LIGATURE = QStringLiteral("insert-ligature");
    const QString MENU_INSERT_MARKS = QStringLiteral("insert-marks");
    const QString MENU_PAGE = QStringLiteral("page");
    const QString MENU_TABLE = QStringLiteral("table");
    const QString MENU_EXTRAS = QStringLiteral("extras");
    const QString MENU_VIEW = QStringLiteral("view");
    const QString MENU_VIEW_ZOOM = QStringLiteral("view-zoom");
    const QString MENU_VIEW_PREVIEW = QStringLiteral("view-preview");
    const QString MENU_VIEW_MEASUREMENT = QStringLiteral("view-measurement");
    const QString MENU_VIEW_TEXTFRAMES = QStringLiteral("view-textframes");
    const QString MENU_VIEW_IMAGEFRAMES = QStringLiteral("view-imageframes");
    const QString MENU_VIEW_DOCUMENT = QStringLiteral("view-document");
    const QString MENU_VIEW_GRIDSGUIDES = QStringLiteral("view-gridsguides");
    const QString MENU_SCRIPT = QStringLiteral("script");
    const QString MENU_SCRIPT_SCRIBUS = QStringLiteral("script-scribus");
    const QString MENU_SCRIPT_RECENT = QStringLiteral("script-recent");
    const QString MENU_WINDOW = QStringLiteral("window");
    const QString MENU_HELP = QStringLiteral("help");


    MenuManager(QObject *parent = nullptr);
    ~MenuManager() = default;

    static MenuManager* m_instance;

    MainWindow *mainWindow;
    QMap<QString, QMenu*> *menuList {nullptr};
    QMap<QString, QMenu*> *menuFileImport {nullptr};



    template<class Obj, typename Func1>
    inline typename std::enable_if<!std::is_same<const char*, Func1>::value
    && QtPrivate::IsPointerToTypeDerivedFromQObject<Obj*>::Value, QAction *>::type
    getAction(const QString &label, QString iconKey, QString shortcutKey, ActionType type, const Obj*receiver, Func1 slot)
    {
        QAction * action = getAction(label, iconKey, shortcutKey, type);

        if(receiver && slot){
            switch(type){
            case ActionType::Normal:
                QObject::connect(action, &QAction::triggered, receiver, std::move(slot));
                break;
            case ActionType::Checkbox:
                QObject::connect(action, &QAction::toggled, receiver, std::move(slot));
                break;
            }

        }

        return action;

    }
    QAction *getAction(const QString &label, QString iconKey, QString shortcutKey, ActionType type = ActionType::Normal, bool checked = false);

    QKeySequence getShortcut(QString key);

    void initFileMenu(QMenu *menu);
    void initFileImportMenu(QMenu *menu);
    void initFileExportMenu(QMenu *menu);
    void initFileOutputPreviewMenu(QMenu *menu);
    void initFileRecentFiles(QMenu *menu);

    void initEditMenu(QMenu *menu);
    void initEditContentsMenu(QMenu *menu);

    void initPageMenu(QMenu *menu);

    void initItemMenu(QMenu *menu);
    void initItemDuplicateTransformMenu(QMenu *menu);
    void initItemGroupingMenu(QMenu *menu);
    void initItemLockingMenu(QMenu *menu);
    void initItemLevelMenu(QMenu *menu);
    void initItemSendToLayerMenu(QMenu *menu);
    void initItemSendToMenu(QMenu *menu);
    void initItemSendToScrapbookMenu(QMenu *menu);
    void initItemAdjustMenu(QMenu *menu);
    void initItemImageMenu(QMenu *menu);
    void initItemImagePreviewSettingsMenu(QMenu *menu);
    void initItemPDFOptionsMenu(QMenu *menu);
    void initItemConvertToMenu(QMenu *menu);
    void initItemTextFrameLinksMenu(QMenu *menu);
    void initItemPathToolsMenu(QMenu *menu);
    void initItemWeldingMenu(QMenu *menu);
    void initItemMarksMenu(QMenu *menu);
    void initItemTextFeaturesMenu(QMenu *menu);

    void initInsertMenu(QMenu *menu);
    void initInsertCharacterMenu(QMenu *menu);
    void initInsertQuoteMenu(QMenu *menu);
    void initInsertSpacesBreaksMenu(QMenu *menu);
    void initInsertLigatureMenu(QMenu *menu);
    void initInsertMarksMenu(QMenu *menu);

    void initTableMenu(QMenu *menu);

    void initExtrasMenu(QMenu *menu);

    void initViewMenu(QMenu *menu);
    void initViewZoomMenu(QMenu *menu);
    void initViewPreviewMenu(QMenu *menu);
    void initViewMeasurementMenu(QMenu *menu);
    void initViewTextFramesMenu(QMenu *menu);
    void initViewImageFramesMenu(QMenu *menu);
    void initViewDocumentMenu(QMenu *menu);
    void initViewGridsGuidesMenu(QMenu *menu);

    void initScriptMenu(QMenu *menu);
    void initScriptScribusScripts(QMenu *menu);
    void initScriptRecentScripts(QMenu *menu);

    void initHelpMenu(QMenu *menu);

};

#endif // MENU_MANAGER_H
