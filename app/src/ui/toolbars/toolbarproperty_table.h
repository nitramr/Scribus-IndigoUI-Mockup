#ifndef TOOLBARPROPERTYTABLE_H
#define TOOLBARPROPERTYTABLE_H

#include "toolbarproperty.h"
#include <QWidget>
#include <QSpinBox>

class ToolBarPropertyTable : public ToolBarProperty
{
public:
    ToolBarPropertyTable(QWidget *parent = nullptr);

private:
    QSpinBox * numberRows;
    QSpinBox * numberColumns;
};

#endif // TOOLBARPROPERTYTABLE_H
