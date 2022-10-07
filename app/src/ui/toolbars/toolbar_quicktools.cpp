#include "toolbar_quicktools.h"
#include "icon_manager.h"

ToolBarQuickTools::ToolBarQuickTools(QWidget *parent) : ToolBarProperty(parent)
{

    IconManager &iconManager = IconManager::instance();

    setIcon( iconManager.icon("scribus-logo").pixmap(QSize(32,32)) );


    quickToolPreview = new QuickToolPreview();
    quickToolLayer = new QuickToolLayer();

    loadWidgets();

}

void ToolBarQuickTools::loadWidgets()
{
    int space = 16;

    this->addWidget(quickToolLayer);
    this->addSpacing(space);
    this->addWidget(quickToolPreview);

}
