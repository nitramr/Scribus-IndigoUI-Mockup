#include "imageeffect_colorize.h"
#include "icon_manager.h"
#include "popup_menu/popup_menu.h"
#include "ui_imageeffect_colorize.h"
#include "widget_manager.h"

/* ********************************************************************************* *
 *
 * Constructor & Setup
 *
 * ********************************************************************************* */

ImageEffectColorize::ImageEffectColorize(Mode mode, QWidget *parent) :
    ImageEffectItem(tr("Colorize"),true, parent),
    ui(new Ui::ImageEffectColorize)
{
    ui->setupUi(this);

    setup();    
    setMode(mode);
    connectSlots();
}

ImageEffectColorize::~ImageEffectColorize()
{
    delete ui;
}

void ImageEffectColorize::setup()
{

    IconManager &iconManager = IconManager::instance();

    ui->buttonCurve1->setIcon(iconManager.icon("curves"));
    ui->buttonCurve2->setIcon(iconManager.icon("curves"));
    ui->buttonCurve3->setIcon(iconManager.icon("curves"));
    ui->buttonCurve4->setIcon(iconManager.icon("curves"));

    // Color Buttons
    ui->buttonColor1->setConfiguration(ColorPickerConfig::Text);
    ui->buttonColor2->setConfiguration(ColorPickerConfig::Text);
    ui->buttonColor3->setConfiguration(ColorPickerConfig::Text);
    ui->buttonColor4->setConfiguration(ColorPickerConfig::Text);


    // Curve Widgets
    curveWidget1 = new ComponentCurveWidget();
    addMenu(ui->buttonCurve1, curveWidget1);

    curveWidget2 = new ComponentCurveWidget();
    addMenu(ui->buttonCurve2, curveWidget2);

    curveWidget3 = new ComponentCurveWidget();
    addMenu(ui->buttonCurve3, curveWidget3);

    curveWidget4 = new ComponentCurveWidget();
    addMenu(ui->buttonCurve4, curveWidget4);

}

void ImageEffectColorize::connectSlots()
{
    connect(ui->buttonColor1, &ColorButton::colorChanged, this, &ImageEffectColorize::setColor1);
    connect(ui->buttonColor2, &ColorButton::colorChanged, this, &ImageEffectColorize::setColor2);
    connect(ui->buttonColor3, &ColorButton::colorChanged, this, &ImageEffectColorize::setColor3);
    connect(ui->buttonColor4, &ColorButton::colorChanged, this, &ImageEffectColorize::setColor4);
}

/* ********************************************************************************* *
 *
 * Private Methods
 *
 * ********************************************************************************* */

void ImageEffectColorize::addMenu(QToolButton *button, QWidget *menuPanel)
{
    PopupMenu * menu = new PopupMenu(menuPanel);
    button->setMenu(menu);
    button->setPopupMode(QToolButton::InstantPopup);
    // button->setStyleSheet( "QToolButton::menu-indicator { image: none; }" );
}

/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

void ImageEffectColorize::setColor1(ScColor color)
{
    ui->buttonColor1->setColor(color);
}

void ImageEffectColorize::setColor2(ScColor color)
{
    ui->buttonColor2->setColor(color);
}

void ImageEffectColorize::setColor3(ScColor color)
{
    ui->buttonColor3->setColor(color);
}

void ImageEffectColorize::setColor4(ScColor color)
{
    ui->buttonColor4->setColor(color);
}


/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

void ImageEffectColorize::setMode(Mode mode)
{
    switch(mode){
    case Mode::Colorize:
        ui->buttonCurve1->setVisible(false);
        ui->layoutColor2->setVisible(false);
        ui->layoutColor3->setVisible(false);
        ui->layoutColor4->setVisible(false);
        this->setText(tr("Colorize"));
        break;
    case Mode::Duotone:
        ui->buttonCurve1->setVisible(true);
        ui->layoutColor2->setVisible(true);
        ui->layoutColor3->setVisible(false);
        ui->layoutColor4->setVisible(false);
        this->setText(tr("Duotone"));
        break;
    case Mode::Tritone:
        ui->buttonCurve1->setVisible(true);
        ui->layoutColor2->setVisible(true);
        ui->layoutColor3->setVisible(true);
        ui->layoutColor4->setVisible(false);
        this->setText(tr("Tritone"));
        break;
    case Mode::Quadtone:
        ui->buttonCurve1->setVisible(true);
        ui->layoutColor2->setVisible(true);
        ui->layoutColor3->setVisible(true);
        ui->layoutColor4->setVisible(true);
        this->setText(tr("Quadtone"));
        break;
    }
}

ImageEffectColorize::Mode ImageEffectColorize::mode()
{
    return m_mode;
}
