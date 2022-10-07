#include "colorblindness_button.h"
#include <QAction>
#include <QMenu>
#include "icon_manager.h"
#include "colorblind.h"


ColorBlindnessButton::ColorBlindnessButton(QWidget *parent) : QToolButton(parent)
{

    IconManager & iconManager = IconManager::instance();

    // Color Blindness
    actionColorBlindNormal  = new QAction(iconManager.icon("colorblind-normal"), tr("Normal Vision"), this);
    actionColorBlindRed     = new QAction(iconManager.icon("colorblind-red"), tr("Protanopia (Red)"), this);
    actionColorBlindGreen   = new QAction(iconManager.icon("colorblind-green"), tr("Deuteranopia (Green)"), this);
    actionColorBlindBlue    = new QAction(iconManager.icon("colorblind-blue"), tr("Tritanopia (Blue)"), this);
    actionColorBlindFull    = new QAction(iconManager.icon("colorblind-full"), tr("Full Color Blindness"), this);

    actionColorBlindNormal->setData( QVariant::fromValue(VisionDefectColor::normalVision) );
    actionColorBlindRed->setData( QVariant::fromValue(VisionDefectColor::protanopeVision) );
    actionColorBlindGreen->setData( QVariant::fromValue(VisionDefectColor::deuteranopeVision) );
    actionColorBlindBlue->setData( QVariant::fromValue(VisionDefectColor::tritanopeVision) );
    actionColorBlindFull->setData( QVariant::fromValue(VisionDefectColor::colorBlindnessVision) );

    menuColorBlind = new QMenu;
    menuColorBlind->addAction(actionColorBlindNormal);
    menuColorBlind->addAction(actionColorBlindRed);
    menuColorBlind->addAction(actionColorBlindGreen);
    menuColorBlind->addAction(actionColorBlindBlue);
    menuColorBlind->addAction(actionColorBlindFull);

    setPopupMode(QToolButton::InstantPopup);
    setMenu(menuColorBlind);
    setDefaultAction(actionColorBlindNormal);

    connectSlots();

}

void ColorBlindnessButton::connectSlots()
{
    connect(this,   &QToolButton::triggered, this, &QToolButton::setDefaultAction);
    connect(actionColorBlindNormal, &QAction::triggered,this, &ColorBlindnessButton::changeColorBlindness );
    connect(actionColorBlindRed,    &QAction::triggered,this, &ColorBlindnessButton::changeColorBlindness );
    connect(actionColorBlindGreen,  &QAction::triggered,this, &ColorBlindnessButton::changeColorBlindness );
    connect(actionColorBlindBlue,   &QAction::triggered,this, &ColorBlindnessButton::changeColorBlindness );
    connect(actionColorBlindFull,   &QAction::triggered,this, &ColorBlindnessButton::changeColorBlindness );
}

void ColorBlindnessButton::changeColorBlindness()
{
    QAction *action = qobject_cast<QAction *>(sender());

    if(action == nullptr) return;

    emit colorBlindnessDefect( static_cast<VisionDefectColor::defectMode>(action->data().toInt()) );
}
