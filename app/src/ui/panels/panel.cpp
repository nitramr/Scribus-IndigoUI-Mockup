#include "panel.h"
#include "popup_menu.h"
#include "icon_manager.h"

Panel::Panel(QWidget *parent)
    : QWidget{parent}
{

}

void Panel::addMenu(SectionContainer *section, QWidget *menuPanel)
{
    PopupMenu * menu = new PopupMenu(menuPanel);
    QToolButton *buttonMenu = new QToolButton();
    buttonMenu->setMenu(menu);
    buttonMenu->setPopupMode(QToolButton::InstantPopup);
    buttonMenu->setIcon(IconManager::instance().icon("more"));
    buttonMenu->setStyleSheet( "QToolButton::menu-indicator { image: none; }" );

    section->addHeaderSuffixWidget(buttonMenu);
}
