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

};

#endif // MENU_MANAGER_H
