#include "imagequality_button.h"
#include "icon_manager.h"
#include <QMenu>

ImageQualityButton::ImageQualityButton(QWidget *parent) : QToolButton(parent)
{
    IconManager & iconManager = IconManager::instance();

    // Color Blindness
    actionQualityLow    = new QAction(iconManager.icon("preview-image-low"), tr("Low Image Resolution"), this);
    actionQualityNormal = new QAction(iconManager.icon("preview-image-normal"), tr("Normal Image Resolution"), this);
    actionQualityHigh   = new QAction(iconManager.icon("preview-image-high"), tr("Full Image Resolution"), this);

    actionQualityLow->setData( QVariant::fromValue(ImageRenderQuality::Low) );
    actionQualityNormal->setData( QVariant::fromValue(ImageRenderQuality::Normal) );
    actionQualityHigh->setData( QVariant::fromValue(ImageRenderQuality::Full) );


    menuQuality = new QMenu;
    menuQuality->addAction(actionQualityHigh);
    menuQuality->addAction(actionQualityNormal);
    menuQuality->addAction(actionQualityLow);


    setPopupMode(QToolButton::InstantPopup);
    setMenu(menuQuality);
    setDefaultAction(actionQualityNormal);

    connectSlots();
}

void ImageQualityButton::connectSlots()
{
    connect(this,   &QToolButton::triggered, this, &QToolButton::setDefaultAction);
    connect(actionQualityLow, &QAction::triggered,this, &ImageQualityButton::changeImageQuality );
    connect(actionQualityNormal,    &QAction::triggered,this, &ImageQualityButton::changeImageQuality );
    connect(actionQualityHigh,  &QAction::triggered,this, &ImageQualityButton::changeImageQuality );
}

void ImageQualityButton::changeImageQuality()
{
    QAction *action = qobject_cast<QAction *>(sender());

    if(action == nullptr) return;

    emit imageQuality( static_cast<ImageRenderQuality>(action->data().toInt()) );
}
