#include "toolbar_quicktools.h"
#include "icon_manager.h"

ToolBarQuickTools::ToolBarQuickTools(QWidget *parent) : ToolBarProperty(parent)
{

    IconManager &iconManager = IconManager::instance();

    setIcon( iconManager.icon("scribus-logo").pixmap(QSize(32,32)) );


    quickToolPreview = new QuickToolPreview();
    quickToolLevel = new QuickToolLevel();
    quickToolPDFTools = new QuickToolPDFTools();
    quickToolEdit = new QuickToolEdit();
    quickToolDocument = new QuickToolDocument();

    loadWidgets();

}

void ToolBarQuickTools::loadWidgets()
{
    int space = 16;

    this->addWidget(quickToolDocument);
    this->addSpacing(space);
    this->addWidget(quickToolEdit);
    this->addSpacing(space);
    this->addWidget(quickToolPreview);
    this->addSpacing(space);
    this->addWidget(quickToolPDFTools);
    this->addSpacing(space);
    this->addWidget(quickToolLevel);
    this->addSpacing(space);

}
