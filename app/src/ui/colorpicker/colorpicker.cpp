#include "colorpicker.h"
#include <QButtonGroup>
#include "iconmanager.h"
#include "ui_colorpicker.h"

#include "menu_popup.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

ColorPicker::ColorPicker(ColorPickerConfig config, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorPicker)
{
    ui->setupUi(this);

    setConfiguration(config);
    setWindowTitle(tr("Color Picker"));

    setup();
    connectSlots();
}

ColorPicker::~ColorPicker()
{
    delete ui;
}


void ColorPicker::setup()
{
    IconManager &iconManager = IconManager::instance();

    ui->buttonSolid->setIcon( iconManager.icon("colorpicker-solid"));
    ui->buttonGradient->setIcon( iconManager.icon("colorpicker-gradient"));

    updatePicker(ItemFillMode::Solid);

    m_buttonGroup = new QButtonGroup();
    m_buttonGroup->addButton(ui->buttonSolid, (int)ItemFillMode::Solid);
    m_buttonGroup->addButton(ui->buttonGradient, (int)ItemFillMode::Gradient);


}

void ColorPicker::connectSlots()
{
    connect(ui->colorEdit, &ColorPickerColor::colorChanged, this, &ColorPicker::updateColor);
    connect(ui->colorEdit, &ColorPickerColor::sizeChanged, this, &ColorPicker::updateSize);
    connect(ui->gradientEdit, &ColorPickerGradient::gradientChanged, this, &ColorPicker::updateGradient);
    connect(ui->gradientEdit, &ColorPickerGradient::sizeChanged, this, &ColorPicker::updateSize);
    connect(m_buttonGroup, &QButtonGroup::buttonClicked, this, &ColorPicker::changedTab);
}

/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

void ColorPicker::setConfiguration(ColorPickerConfig config)
{
    m_configuration = config;

    ui->colorEdit->setConfiguration(m_configuration);
    ui->gradientEdit->setConfiguration(m_configuration);

    switch(m_configuration){
    // Solid, Gradient, Hatch
    case ColorPickerConfig::Fill:
        ui->buttonSolid->setVisible(true);
        ui->buttonGradient->setVisible(true);
        break;
    // Solid Gradient
    case ColorPickerConfig::FillMask:
    case ColorPickerConfig::Stroke:
        ui->buttonSolid->setVisible(true);
        ui->buttonGradient->setVisible(true);
        break;
    // Solid
    case ColorPickerConfig::StrokeMask:
    case ColorPickerConfig::Text:
    case ColorPickerConfig::Shadow:
    case ColorPickerConfig::Default:
    default:
        ui->buttonSolid->setVisible(false);
        ui->buttonGradient->setVisible(false);

        break;
    }

    ui->colorEdit->setVisible(true);
    ui->gradientEdit->setVisible(false);

    //ui->stack->setCurrentIndex(0);

    /*
    =Default=
        Solid:
            - Slider
            - Map
            - Alpha

    =Fill=
        Solid:
            - Slider
            - Map
            - Harmony
            - Swatches
            - Alpha
            - Shade
        Gradient:
            - Linear
            - Radial
            - Conical
            - Diamond
            - 4 Colors
            - Mesh
            - Patch Mesh
        Hatch

    =Fill Mask=
        Solid:
            - Alpha
        Gradient:
            - Linear
            - Radial

    =Stroke=
        Solid:
            - Slider
            - Map
            - Harmony
            - Swatches
            - Alpha
            - Shade
        Gradient:
            - Linear
            - Radial

    =Stroke Mask=
        Solid:
            - Alpha

    =Text=
        Solid:
            - Slider
            - Map
            - Harmony
            - Swatches
            - Alpha
            - Shade

    =Shadow=
        Solid:
            - Slider
            - Map
            - Harmony
            - Swatches
            - Alpha
            - Shade


      */

}

ColorPickerConfig ColorPicker::configuration()
{
    return m_configuration;
}

/* ********************************************************************************* *
 *
 * Public Slots
 *
 * ********************************************************************************* */


//void ColorPicker::setColorButton(ColorButton *button)
//{
//    //    PopupMenu * menu = new PopupMenu(this);
//    //    menu->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);

//    m_colorButton = button;
//    //    m_colorButton->setCheckable(true);
//    //    m_colorButton->setMenu(menu);

//    //    connect(m_colorButton, &ColorButton::toggled, this, [menu](bool t) {
//    //        menu->setVisible(t);

//    //    });

//    m_colorButton->setContextWidget(this);

//}

void ColorPicker::setColor(ScColor color)
{
    m_color = color;
    ui->colorEdit->setColor(color);
    updatePicker(ItemFillMode::Solid);
}

void ColorPicker::setGradient(VGradient gradient)
{
    m_gradient = gradient;
    ui->gradientEdit->setGradient(gradient);
    updatePicker(ItemFillMode::Gradient);
}

void ColorPicker::setPattern()
{
    updatePicker(ItemFillMode::Pattern);
}

void ColorPicker::setImage()
{
    updatePicker(ItemFillMode::Image);
}

/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

//void ColorPicker::updateColorButton()
//{
//    switch(m_fillMode){
//    case ItemFillMode::Solid:
//        m_colorButton->setColor(m_color);
//        break;
//    case ItemFillMode::Gradient:
//        m_colorButton->setGradient(m_gradient);
//        break;
//    case ItemFillMode::Pattern:

//        break;
//    case ItemFillMode::Image:

//        break;

//    }

//}

void ColorPicker::updateColor(ScColor color)
{
    m_color = color;
  //  updateColorButton();
    emit colorChanged(m_color);
}

void ColorPicker::updateGradient(VGradient gradient)
{
    m_gradient = gradient;
  //  updateColorButton();
    emit gradientChanged(m_gradient);
}

void ColorPicker::updatePattern()
{
 //   updateColorButton();
    emit patternChanged();
}

void ColorPicker::updateImage()
{
//    updateColorButton();
    emit imageChanged();
}

void ColorPicker::updateSize()
{
    this->adjustSize();

    QWidget *parentWidget = qobject_cast<QWidget*>(parent());
    if(parentWidget){
        parentWidget->adjustSize();
    }
}

void ColorPicker::updatePicker(ItemFillMode mode)
{
    m_fillMode = mode;

    switch(m_fillMode){
    default:
    case ItemFillMode::Solid:
        ui->colorEdit->setVisible(true);
        ui->gradientEdit->setVisible(false);

        break;
    case ItemFillMode::Gradient:
        ui->colorEdit->setVisible(false);
        ui->gradientEdit->setVisible(true);

        break;
    case ItemFillMode::Pattern:

        break;
    case ItemFillMode::Image:

        break;

    }

    updateSize();

}

void ColorPicker::changedTab()
{
    ItemFillMode fillMode = static_cast<ItemFillMode>(m_buttonGroup->checkedId());
    updatePicker(fillMode);

    switch(fillMode){
    default:
    case ItemFillMode::Solid:
        updateColor(m_color);       

        break;
    case ItemFillMode::Gradient:
        updateGradient(m_gradient);

        break;
    }

}



