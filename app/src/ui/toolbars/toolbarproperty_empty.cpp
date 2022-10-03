#include "toolbarproperty_empty.h"

#include <QLabel>

ToolBarPropertyEmpty::ToolBarPropertyEmpty(QWidget *parent) : ToolBarProperty(parent)
{
    addWidget(new QLabel(tr("Tool properties appear here if you select a tool.")));
}
