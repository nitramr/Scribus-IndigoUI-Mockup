#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <QMenu>
#include <QMenuBar>
#include <QPointer>
#include <QToolBar>

class MainWindow;

class ActionManager : public QObject
{

    Q_OBJECT

public:
    //ActionManager(QMenuBar *menu, MainWindow *mainWindow);
    ActionManager(ActionManager const&) = delete;
    void operator=(ActionManager const&) = delete;
    static ActionManager& instance();

    void setup(MainWindow *window);

    QMenu *menuWindow();

    void initToolBar(QToolBar * toolbar);
    void initRootMenu(QMenuBar *menu);

private:
    ActionManager(QObject *parent = nullptr);
    ~ActionManager() = default;

    static ActionManager* m_instance;

    MainWindow *mainWindow;
    QMap<QString, QMenu*> *menuList {nullptr};


    void initFileMenu();
};

#endif // ACTIONMANAGER_H
