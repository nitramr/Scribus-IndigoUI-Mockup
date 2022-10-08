#ifndef TOOLBARPROPERTYBASE_H
#define TOOLBARPROPERTYBASE_H

#include "form_widget/form_widget.h"
#include <QToolBar>
#include <QLabel>
#include <QMap>

class ToolBarProperty : public QToolBar
{
public:
    ToolBarProperty(QWidget *parent = nullptr);

    void setIcon(QPixmap icon);
    void addSpacing(int spacing);
    FormWidget * addFormWidget(QString key, QString label, QList<QWidget*> widgets);

    void formWidgetVisibility(QString key, bool visible);

private:
    QLabel* m_icon;
    QMap<QString,QAction*> *m_formWidgets;

    int minHeight();

};

#endif // TOOLBARPROPERTYBASE_H
