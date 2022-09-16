#ifndef PANEL_H
#define PANEL_H

#include "section_container/section_container.h"
#include <QWidget>

class Panel : public QWidget
{
    Q_OBJECT
public:
    explicit Panel(QWidget *parent = nullptr);

    void addMenu(SectionContainer *section, QWidget *menuPanel);

signals:

};

#endif // PANEL_H
