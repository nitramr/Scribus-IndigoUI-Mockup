#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ActionManager;
class IconManager;
class DockManager;
class ThemeManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class ActionManager;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void saveState();
    void restoreState();

private:
    Ui::MainWindow *ui;

    // Manager
    IconManager& iconManager;
    ActionManager &actionManager;
    ThemeManager &themeManager;
    DockManager *dockManager;

    void initMenu();
    void initToolBars();

public slots:

    void dummySlot();

    void newDocument();
    void openDocument();



};
#endif // MAINWINDOW_H
