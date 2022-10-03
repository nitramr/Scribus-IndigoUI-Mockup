#ifndef TOOLBARPROPERTYBASE_H
#define TOOLBARPROPERTYBASE_H

#include <QToolBar>
#include <QLabel>

class ToolBarProperty : public QToolBar
{
public:
    ToolBarProperty(QWidget *parent = nullptr);

    void setIcon(QPixmap icon);
    void addSpacing(int spacing);

private:
    QLabel* m_icon;

    int calculateMinHeight();

};

#endif // TOOLBARPROPERTYBASE_H
