#include "block_imageeffects.h"
#include "imageeffect_blur.h"
#include "imageeffect_brightness.h"
#include "imageeffect_colorize.h"
#include "imageeffect_contrast.h"
#include "imageeffect_curves.h"
#include "imageeffect_grayscale.h"
#include "imageeffect_invert.h"
#include "imageeffect_posterize.h"
#include "imageeffect_sharpen.h"
#include "ui_block_imageeffects.h"
#include "enums.h"
#include "icon_manager.h"

#include <QAction>

/* ********************************************************************************* *
 *
 * Constructor & Setup
 *
 * ********************************************************************************* */

BlockImageEffects::BlockImageEffects(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockImageEffects)
{
    ui->setupUi(this);
    setup();
    connectSlots();
}

BlockImageEffects::~BlockImageEffects()
{
    delete ui;
}

void BlockImageEffects::setup()
{

    IconManager & iconManager = IconManager::instance();

    // Image Effects
    actionEffectBlur        = new QAction(iconManager.icon("image-effects"), "Blur", this);
    actionEffectBrightness  = new QAction(iconManager.icon("image-effects"), "Brightness", this);
    actionEffectColorize    = new QAction(iconManager.icon("image-effects"), "Colorize", this);
    actionEffectDuotone     = new QAction(iconManager.icon("image-effects"), "Duotone", this);
    actionEffectTritone     = new QAction(iconManager.icon("image-effects"), "Tritone", this);
    actionEffectQuadtone    = new QAction(iconManager.icon("image-effects"), "Quadtone", this);
    actionEffectContrast    = new QAction(iconManager.icon("image-effects"), "Contrast", this);
    actionEffectGrayscale   = new QAction(iconManager.icon("image-effects"), "Grayscale", this);
    actionEffectCurves      = new QAction(iconManager.icon("image-effects"), "Curves", this);
    actionEffectInvert      = new QAction(iconManager.icon("image-effects"), "Invert", this);
    actionEffectPosterize   = new QAction(iconManager.icon("image-effects"), "Posterize", this);
    actionEffectSharpen     = new QAction(iconManager.icon("image-effects"), "Sharpen", this);

    actionEffectBlur->setData( QVariant::fromValue(ImageEffects::Blur) );
    actionEffectBrightness->setData( QVariant::fromValue(ImageEffects::Brightness) );
    actionEffectColorize->setData( QVariant::fromValue(ImageEffects::Colorize) );
    actionEffectDuotone->setData( QVariant::fromValue(ImageEffects::Duotone) );
    actionEffectTritone->setData( QVariant::fromValue(ImageEffects::Tritone) );
    actionEffectQuadtone->setData( QVariant::fromValue(ImageEffects::Quadtone) );
    actionEffectContrast->setData( QVariant::fromValue(ImageEffects::Contrast) );
    actionEffectGrayscale->setData( QVariant::fromValue(ImageEffects::Grayscale) );
    actionEffectCurves->setData( QVariant::fromValue(ImageEffects::Curves) );
    actionEffectInvert->setData( QVariant::fromValue(ImageEffects::Invert) );
    actionEffectPosterize->setData( QVariant::fromValue(ImageEffects::Posterize) );
    actionEffectSharpen->setData( QVariant::fromValue(ImageEffects::Sharpen) );

    menuImageEffects = new QMenu;
    menuImageEffects->addAction(actionEffectBlur);
    menuImageEffects->addAction(actionEffectBrightness);
    menuImageEffects->addAction(actionEffectColorize);
    menuImageEffects->addAction(actionEffectDuotone);
    menuImageEffects->addAction(actionEffectTritone);
    menuImageEffects->addAction(actionEffectQuadtone);
    menuImageEffects->addAction(actionEffectContrast);
    menuImageEffects->addAction(actionEffectGrayscale);
    menuImageEffects->addAction(actionEffectCurves);
    menuImageEffects->addAction(actionEffectInvert);
    menuImageEffects->addAction(actionEffectPosterize);
    menuImageEffects->addAction(actionEffectSharpen);


    // Buttons
    ui->buttonAddEffect->setMenu(menuImageEffects);
    ui->buttonAddEffect->setIcon( iconManager.icon("add") );
    ui->buttonMoveDown->setIcon( iconManager.icon("move-down") );
    ui->buttonMoveUp->setIcon( iconManager.icon("move-up") );



}

void BlockImageEffects::connectSlots()
{
    connect(actionEffectBlur,       &QAction::triggered,this, &BlockImageEffects::addImageEffect );
    connect(actionEffectBrightness, &QAction::triggered,this, &BlockImageEffects::addImageEffect );
    connect(actionEffectColorize,   &QAction::triggered,this, &BlockImageEffects::addImageEffect );
    connect(actionEffectDuotone,    &QAction::triggered,this, &BlockImageEffects::addImageEffect );
    connect(actionEffectTritone,    &QAction::triggered,this, &BlockImageEffects::addImageEffect );
    connect(actionEffectQuadtone,   &QAction::triggered,this, &BlockImageEffects::addImageEffect );
    connect(actionEffectContrast,   &QAction::triggered,this, &BlockImageEffects::addImageEffect );
    connect(actionEffectGrayscale,  &QAction::triggered,this, &BlockImageEffects::addImageEffect );
    connect(actionEffectCurves,     &QAction::triggered,this, &BlockImageEffects::addImageEffect );
    connect(actionEffectInvert,     &QAction::triggered,this, &BlockImageEffects::addImageEffect );
    connect(actionEffectPosterize,  &QAction::triggered,this, &BlockImageEffects::addImageEffect );
    connect(actionEffectSharpen,    &QAction::triggered,this, &BlockImageEffects::addImageEffect );
}


/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

void BlockImageEffects::addImageEffect()
{

    QAction *action = qobject_cast<QAction *>(sender());

    if(action == nullptr) return;

    ImageEffects m_effect = static_cast<ImageEffects>(action->data().toInt());

    switch(m_effect){
    case ImageEffects::Blur:{

        ImageEffectBlur * effectWidget = new ImageEffectBlur();
        ui->imageeffectList->addItem(effectWidget);

        break;
    }
    case ImageEffects::Brightness:{

        ImageEffectBrightness * effectWidget = new ImageEffectBrightness();
        ui->imageeffectList->addItem(effectWidget);

        break;
    }
    case ImageEffects::Colorize:{

        ImageEffectColorize * effectWidget = new ImageEffectColorize();
        ui->imageeffectList->addItem(effectWidget);

        break;
    }
    case ImageEffects::Duotone:{

        ImageEffectColorize * effectWidget = new ImageEffectColorize(ImageEffectColorize::Duotone);
        ui->imageeffectList->addItem(effectWidget);

        break;
    }
    case ImageEffects::Tritone:{

        ImageEffectColorize * effectWidget = new ImageEffectColorize(ImageEffectColorize::Tritone);
        ui->imageeffectList->addItem(effectWidget);

        break;
    }
    case ImageEffects::Quadtone:{

        ImageEffectColorize * effectWidget = new ImageEffectColorize(ImageEffectColorize::Quadtone);
        ui->imageeffectList->addItem(effectWidget);

        break;
    }
    case ImageEffects::Contrast:{

        ImageEffectContrast * effectWidget = new ImageEffectContrast();
        ui->imageeffectList->addItem(effectWidget);

        break;
    }
    case ImageEffects::Grayscale:{

        ImageEffectGrayscale * effectWidget = new ImageEffectGrayscale();
        ui->imageeffectList->addItem(effectWidget);

        break;
    }
    case ImageEffects::Curves:{

        ImageEffectCurves * effectWidget = new ImageEffectCurves();
        ui->imageeffectList->addItem(effectWidget);

        break;
    }
    case ImageEffects::Invert:{

        ImageEffectInvert * effectWidget = new ImageEffectInvert();
        ui->imageeffectList->addItem(effectWidget);

        break;
    }
    case ImageEffects::Posterize:{

        ImageEffectPosterize * effectWidget = new ImageEffectPosterize();
        ui->imageeffectList->addItem(effectWidget);

        break;
    }
    case ImageEffects::Sharpen:{

        ImageEffectSharpen * effectWidget = new ImageEffectSharpen();
        ui->imageeffectList->addItem(effectWidget);

        break;
    }
    }

}

