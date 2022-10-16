#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include "icon_manager.h"
#include "shortcut_manager.h"
#include <QMenu>
#include <QMenuBar>
#include <QPointer>
#include <QToolBar>

class MainWindow;

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

private:

    const QString MENU_FILE = QStringLiteral("file");
    const QString MENU_FILE_IMPORT = QStringLiteral("file-import");
    const QString MENU_FILE_EXPORT = QStringLiteral("file-export");
    const QString MENU_FILE_OUTPUTPREVIEW = QStringLiteral("file-outputpreview");
    const QString MENU_FILE_RECENTFILES = QStringLiteral("file-recentfiles");
    const QString MENU_EDIT = QStringLiteral("edit");
    const QString MENU_EDIT_CONTENTS = QStringLiteral("edit-contents");
    const QString MENU_ITEM = QStringLiteral("item");
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
    getAction(const QString &label, QString iconKey, QString shortcutKey, bool checkable, const Obj*receiver, Func1 slot)
        {
           QAction * action = getAction(label, iconKey, shortcutKey, checkable);

           if(receiver && slot)
                QObject::connect(action, &QAction::triggered, receiver, std::move(slot));

           return action;

    }
    QAction *getAction(const QString &label, QString iconKey, QString shortcutKey, bool checkable = false);

    QKeySequence getShortcut(QString key);

    void initFileMenu();
    void initFileImportMenu();
    void initFileExportMenu();
    void initFileOutputPreviewMenu();
    void initFileRecentFiles();

    void initEditMenu();
    void initEditContentsMenu();

    void initPageMenu();

    void initInsertMenu();

    void initTableMenu();

    void initExtrasMenu();

    void initViewMenu();
    void initViewZoomMenu();
    void initViewPreviewMenu();
    void initViewMeasurementMenu();
    void initViewTextFramesMenu();
    void initViewImageFramesMenu();
    void initViewDocumentMenu();
    void initViewGridsGuidesMenu();

    void initScriptMenu();
    void initScriptScribusScripts();
    void initScriptRecentScripts();

    void initHelpMenu();

};

#endif // MENU_MANAGER_H
