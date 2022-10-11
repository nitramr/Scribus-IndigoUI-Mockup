#include "toolbarproperty_table.h"
#include "icon_manager.h"

ToolBarPropertyTable::ToolBarPropertyTable(QWidget *parent) : ToolBarProperty(parent)
{

    IconManager &iconManager = IconManager::instance();

    setIcon( iconManager.pixmap("tool-table") );


    numberRows = new QSpinBox;
    numberRows->setMinimum(1);

    numberColumns = new QSpinBox;
    numberColumns->setMinimum(1);

    this->addFormWidget("row", tr("Rows:"), QList<QWidget*>() << numberRows );
    this->addFormWidget("columns", tr("Columns:"), QList<QWidget*>() << numberColumns );

}
