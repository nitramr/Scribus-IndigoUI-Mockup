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

    FormWidget * formWidget(QString key);
    void setFormWidgetVisibility(QString key, bool visible);
    void setFormWidgetLabel(QString key, QString label);

public slots:
    void setIconSize(const QSize &iconSize);

private:
    QLabel* m_icon;
    QPixmap m_pixmap;
    QMap<QString,QAction*> *m_formWidgets;

    int minHeight();

};

#endif // TOOLBARPROPERTYBASE_H
