#include "imageeffect_item.h"
#include "icon_manager.h"


ImageEffectItem::ImageEffectItem(QString title, bool isCollapsible, QWidget *parent) : SectionContainer(title, isCollapsible, parent)
{

    internalSetup();
    internalConnectSlots();

}


void ImageEffectItem::internalSetup()
{

    IconManager &iconManager = IconManager::instance();
    QIcon iconClose = iconManager.icon("chevron-right");
    QIcon iconOpen = iconManager.icon("chevron-down");
    QIcon iconDelete = iconManager.icon("delete");


    checkBoxEffect = new QCheckBox();
    checkBoxEffect->setCheckState(Qt::Checked);
    buttonDelete = new QToolButton();
    buttonDelete->setIcon(iconDelete);

    addHeaderPrefixWidget(checkBoxEffect);
    addHeaderSuffixWidget(buttonDelete);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    setCollapseIcons(iconClose, iconOpen);
    setHasStyle(false);
    setSizePolicy(sizePolicy);
//    setMaximumWidth(300);


}

void ImageEffectItem::internalConnectSlots()
{
    connect(buttonDelete, &QToolButton::clicked, this, &ImageEffectItem::removeItem );
}

void ImageEffectItem::removeItem()
{
    this->deleteLater();
    //delete this;
}
