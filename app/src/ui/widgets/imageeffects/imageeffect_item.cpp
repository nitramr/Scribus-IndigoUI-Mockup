#include "imageeffect_item.h"
#include "icon_manager.h"


ImageEffectItem::ImageEffectItem(QString title, bool isCollapsible, QWidget *parent) : SectionContainer(title, isCollapsible, parent)
{

    setup();

}

void ImageEffectItem::setup()
{

    IconManager &iconManager = IconManager::instance();
    QIcon iconClose = iconManager.icon("chevron-right");
    QIcon iconOpen = iconManager.icon("chevron-down");
    QIcon iconDelete = iconManager.icon("delete");


    checkBoxEffect = new QCheckBox();
    buttonDelete = new QToolButton();
    buttonDelete->setIcon(iconDelete);

    addHeaderPrefixWidget(checkBoxEffect);
    addHeaderSuffixWidget(buttonDelete);

    setCollapseIcons(iconClose, iconOpen);


}
