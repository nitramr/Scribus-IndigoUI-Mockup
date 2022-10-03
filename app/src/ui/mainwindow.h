#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MenuManager;
class IconManager;
class DockManager;
class ThemeManager;
class WidgetManager;
class ToolbarManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class MenuManager;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void saveState();
    void restoreState();

private:
    Ui::MainWindow *ui;

    // Manager
    DockManager *dockManager;
    IconManager &iconManager;
    MenuManager &menuManager;
    ThemeManager &themeManager;
    WidgetManager &widgetManager;
    ToolbarManager &toolbarManager;



    void initMenu();
    void initToolBars();

public slots:

    void dummySlot();

    void newDocument();
    void openDocument();



};
#endif // MAINWINDOW_H
