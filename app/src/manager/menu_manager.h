#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

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
    const QString MENU_EDIT = QStringLiteral("edit");
    const QString MENU_ITEM = QStringLiteral("item");
    const QString MENU_INSERT = QStringLiteral("insert");
    const QString MENU_PAGE = QStringLiteral("page");
    const QString MENU_TABLE = QStringLiteral("table");
    const QString MENU_EXTRAS = QStringLiteral("extras");
    const QString MENU_VIEW = QStringLiteral("view");
    const QString MENU_SCRIPT = QStringLiteral("script");
    const QString MENU_WINDOW = QStringLiteral("window");
    const QString MENU_HELP = QStringLiteral("help");

    MenuManager(QObject *parent = nullptr);
    ~MenuManager() = default;

    static MenuManager* m_instance;

    MainWindow *mainWindow;
    QMap<QString, QMenu*> *menuList {nullptr};
    QMap<QString, QMenu*> *menuFileImport {nullptr};


    void initFileMenu();
    void initFileImportMenu();
    void initFileExportMenu();
    void initFileOutputPreviewMenu();

    void initEditMenu();

    void initPageMenu();

};

#endif // MENU_MANAGER_H
