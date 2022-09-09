#include "colorpicker_gradient.h"
#include "iconmanager.h"
#include "ui_colorpicker_gradient.h"
#include "menu_popup.h"
#include "enums.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

ColorPickerGradient::ColorPickerGradient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorPickerGradient)
{
    ui->setupUi(this);

    setWindowTitle(tr("Edit Gradient"));

    setup();
    connectSlots();
}

ColorPickerGradient::~ColorPickerGradient()
{
    delete ui;
}

void ColorPickerGradient::setup()
{
    IconManager & iconManager = IconManager::instance();

    QIcon iconCollapsed = iconManager.icon("chevron-right");
    QIcon iconOpen = iconManager.icon("chevron-down");

    m_gradient = VGradient(GradientType::Linear);
    ui->stackGradientPicker->setCurrentIndex(0);

    // Sections
    ui->sectionGradient->setCollapseIcons(iconCollapsed, iconOpen);
    ui->sectionGradient->addHeaderWidget(ui->comboType);
    ui->sectionSwatches->setCollapseIcons(iconCollapsed, iconOpen);

    // Buttons
    ui->buttonAddGradient->setIcon(iconManager.icon("add"));

    // Picker Type
    ui->comboType->addItem(tr("Linear"), QVariant::fromValue(GradientType::Linear));
    ui->comboType->addItem(tr("Radial"), QVariant::fromValue(GradientType::Radial));
    ui->comboType->addItem(tr("Conical"), QVariant::fromValue(GradientType::Conical));
    ui->comboType->addItem(tr("Diamond"), QVariant::fromValue(GradientType::Diamond));
    ui->comboType->addItem(tr("4 Colors"), QVariant::fromValue(GradientType::FourColors));
    ui->comboType->addItem(tr("Mesh"), QVariant::fromValue(GradientType::Mesh));
    ui->comboType->addItem(tr("Patch Mesh"), QVariant::fromValue(GradientType::PatchMesh));

    // Fill Picker
    colorPickerEdit = new ColorPickerColor(ColorPickerConfig::Fill);
    colorPickerMeshNode = new ColorPickerColor(ColorPickerConfig::Fill);
    colorPicker4CTopLeft = new ColorPickerColor(ColorPickerConfig::Fill);
    colorPicker4CTopRight = new ColorPickerColor(ColorPickerConfig::Fill);
    colorPicker4CBottomLeft = new ColorPickerColor(ColorPickerConfig::Fill);
    colorPicker4CBottomRight = new ColorPickerColor(ColorPickerConfig::Fill);

    ui->buttonColor->setContextWidget(colorPickerEdit, true);
    ui->buttonMeshNode->setContextWidget(colorPickerMeshNode, true);
    ui->button4CTopLeft->setContextWidget(colorPicker4CTopLeft, true);
    ui->button4CTopRight->setContextWidget(colorPicker4CTopRight, true);
    ui->button4CBottomLeft->setContextWidget(colorPicker4CBottomLeft, true);
    ui->button4CBottomRight->setContextWidget(colorPicker4CBottomRight, true);

    // Swatches
    ui->swatches->setConfiguration(ItemFillMode::Gradient);

    // Default Values
    ScColor baseGradient = ui->gradientEdit->gradient().colorStops().first()->color;
    ui->buttonColor->setColor(baseGradient);
    colorPickerEdit->setColor(baseGradient);

}

void ColorPickerGradient::connectSlots()
{

    connect(ui->comboType, &QComboBox::currentIndexChanged, this, &ColorPickerGradient::changeSelectorMode);

    connect(ui->gradientEdit, &GradientEdit::selectedColor, this, &ColorPickerGradient::updateSimpleGradientColor);
    connect(ui->gradientEdit, &GradientEdit::selectedPosition, this, &ColorPickerGradient::updateSimpleGradientInputPosition);

    connect(ui->numberPosition, &QSpinBox::valueChanged, this, &ColorPickerGradient::updateSimpleGradientStep);

    connect(colorPickerEdit, &ColorPickerColor::colorChanged, this, &ColorPickerGradient::updateSimpleGradientColor);
    connect(colorPickerMeshNode, &ColorPickerColor::colorChanged, this, &ColorPickerGradient::updateMeshNodeGradientColor);
    connect(colorPicker4CTopLeft, &ColorPickerColor::colorChanged, this, &ColorPickerGradient::update4ColorGradientColor);
    connect(colorPicker4CTopRight, &ColorPickerColor::colorChanged, this, &ColorPickerGradient::update4ColorGradientColor);
    connect(colorPicker4CBottomLeft, &ColorPickerColor::colorChanged, this, &ColorPickerGradient::update4ColorGradientColor);
    connect(colorPicker4CBottomRight, &ColorPickerColor::colorChanged, this, &ColorPickerGradient::update4ColorGradientColor);

    // Sections
    connect(ui->sectionGradient,      &SectionContainer::collapsedState, this, &ColorPickerGradient::changeSize);
    connect(ui->sectionSwatches,    &SectionContainer::collapsedState, this, &ColorPickerGradient::changeSize);

    // connect(ui->buttonColor, &QToolButton::pressed, this, &ColorPickerGradient::openColorPicker);
}

void ColorPickerGradient::disconnectSlots()
{
    disconnect(ui->comboType, &QComboBox::currentIndexChanged, this, &ColorPickerGradient::changeSelectorMode);

    disconnect(ui->gradientEdit, &GradientEdit::selectedColor, this, &ColorPickerGradient::updateSimpleGradientColor);
    disconnect(ui->gradientEdit, &GradientEdit::selectedPosition, this, &ColorPickerGradient::updateSimpleGradientInputPosition);

    disconnect(ui->numberPosition, &QSpinBox::valueChanged, this, &ColorPickerGradient::updateSimpleGradientStep);

    disconnect(colorPickerEdit, &ColorPickerColor::colorChanged, this, &ColorPickerGradient::updateSimpleGradientColor);
    disconnect(colorPickerMeshNode, &ColorPickerColor::colorChanged, this, &ColorPickerGradient::updateMeshNodeGradientColor);
    disconnect(colorPicker4CTopLeft, &ColorPickerColor::colorChanged, this, &ColorPickerGradient::update4ColorGradientColor);
    disconnect(colorPicker4CTopRight, &ColorPickerColor::colorChanged, this, &ColorPickerGradient::update4ColorGradientColor);
    disconnect(colorPicker4CBottomLeft, &ColorPickerColor::colorChanged, this, &ColorPickerGradient::update4ColorGradientColor);
    disconnect(colorPicker4CBottomRight, &ColorPickerColor::colorChanged, this, &ColorPickerGradient::update4ColorGradientColor);

    // Sections
    disconnect(ui->sectionGradient,      &SectionContainer::collapsedState, this, &ColorPickerGradient::changeSize);
    disconnect(ui->sectionSwatches,    &SectionContainer::collapsedState, this, &ColorPickerGradient::changeSize);

}

/* ********************************************************************************* *
 *
 * Members
 *
 * ********************************************************************************* */

VGradient ColorPickerGradient::gradient()
{
    return m_gradient;
}

void ColorPickerGradient::setConfiguration(ColorPickerConfig config)
{
    m_configuration = config;

    disconnectSlots();

    // reset controls
    ui->comboType->clear();

    switch(m_configuration){

    case ColorPickerConfig::Stroke:
    case ColorPickerConfig::FillMask:
        ui->comboType->addItem(tr("Linear"), QVariant::fromValue(GradientType::Linear));
        ui->comboType->addItem(tr("Radial"), QVariant::fromValue(GradientType::Radial));
        ui->comboType->setCurrentIndex(0);
        break;

    case ColorPickerConfig::Fill:
        ui->comboType->addItem(tr("Linear"), QVariant::fromValue(GradientType::Linear));
        ui->comboType->addItem(tr("Radial"), QVariant::fromValue(GradientType::Radial));
        ui->comboType->addItem(tr("Conical"), QVariant::fromValue(GradientType::Conical));
        ui->comboType->addItem(tr("Diamond"), QVariant::fromValue(GradientType::Diamond));
        ui->comboType->addItem(tr("4 Colors"), QVariant::fromValue(GradientType::FourColors));
        ui->comboType->addItem(tr("Mesh"), QVariant::fromValue(GradientType::Mesh));
        ui->comboType->addItem(tr("Patch Mesh"), QVariant::fromValue(GradientType::PatchMesh));
        ui->comboType->setCurrentIndex(0);
        break;
    case ColorPickerConfig::StrokeMask:
    case ColorPickerConfig::Text:
    case ColorPickerConfig::Shadow:
    case ColorPickerConfig::Default:

        break;
    }



    connectSlots();
}

ColorPickerConfig ColorPickerGradient::configuration()
{
    return m_configuration;
}

/* ********************************************************************************* *
 *
 * Private Methods
 *
 * ********************************************************************************* */

void ColorPickerGradient::changeUI()
{

    switch(m_mode){
    default:
    case GradientType::Linear:
    case GradientType::Radial:
    case GradientType::Conical:
    case GradientType::Diamond:
        ui->stackGradientPicker->setCurrentIndex(0);
        break;
    case GradientType::FourColors:
        ui->stackGradientPicker->setCurrentIndex(1);
        break;
    case GradientType::Mesh:
    case GradientType::PatchMesh:
        ui->stackGradientPicker->setCurrentIndex(2);
        break;    
    }

}

void ColorPickerGradient::createGradient()
{
    switch(m_mode){
    default:
    case GradientType::Linear:
    case GradientType::Radial:
    case GradientType::Conical:
    case GradientType::Diamond:
        m_gradient = ui->gradientEdit->gradient();
        m_gradient.setType(m_mode);

        break;
    case GradientType::FourColors:{

        VGradient gradient4Color(GradientType::FourColors);
        ScColor col = ui->button4CTopLeft->color();
        gradient4Color.addStop(col, .0, .5, col.alphaF(), col.name());
        col = ui->button4CTopRight->color();
        gradient4Color.addStop(col, 1. / 3, .5, col.alphaF(), col.name());
        col = ui->button4CBottomLeft->color();
        gradient4Color.addStop(col, 1. / 3 * 2, .5, col.alphaF(), col.name());
        col = ui->button4CBottomRight->color();
        gradient4Color.addStop(col, 1., .5, col.alphaF(), col.name());

        m_gradient = gradient4Color;

    }
        break;
    case GradientType::Mesh:
        // TODO: set Gradient (m_gradient)
        break;
    case GradientType::PatchMesh:
        // TODO: set Gradient (m_gradient)
        break;
    }



}

/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

void ColorPickerGradient::changeSelectorMode()
{
    m_mode = static_cast<GradientType>(ui->comboType->currentData(Qt::UserRole).toInt());
    changeUI();
    createGradient();
    emit gradientChanged(m_gradient);
}


void ColorPickerGradient::openColorPicker()
{
    // colorPickerEdit->setColor(ui->gradientPreview.)
}

void ColorPickerGradient::update4ColorGradientColor(ScColor color)
{
    if( colorPicker4CTopLeft        == qobject_cast<ColorPickerColor*>(sender()) )   ui->button4CTopLeft->setColor(color);
    if( colorPicker4CTopRight       == qobject_cast<ColorPickerColor*>(sender()) )   ui->button4CTopRight->setColor(color);
    if( colorPicker4CBottomLeft     == qobject_cast<ColorPickerColor*>(sender()) )   ui->button4CBottomLeft->setColor(color);
    if( colorPicker4CBottomRight    == qobject_cast<ColorPickerColor*>(sender()) )   ui->button4CBottomRight->setColor(color);

    createGradient();
    emit gradientChanged(m_gradient);
}

void ColorPickerGradient::updateMeshNodeGradientColor(ScColor color)
{
    ui->buttonMeshNode->setColor(color);

    createGradient();
    emit gradientChanged(m_gradient);
}

void ColorPickerGradient::updateSimpleGradientColor(ScColor color)
{

    if( colorPickerEdit            != qobject_cast<ColorPickerColor*>(sender()) )   colorPickerEdit->setColor(color);
    if( ui->gradientEdit           != qobject_cast<GradientEdit*>(sender()) )       ui->gradientEdit->setActiveStopColor(color);

    ui->buttonColor->setColor(color);

    createGradient();
    emit gradientChanged(m_gradient);

}

void ColorPickerGradient::updateSimpleGradientInputPosition(double position)
{
    ui->numberPosition->setValue(position * 100);
}

void ColorPickerGradient::updateSimpleGradientStep(int position)
{
    ui->gradientEdit->setActiveStopPosition((double)position/100);
}

/* ********************************************************************************* *
 *
 * Public Slots
 *
 * ********************************************************************************* */

void ColorPickerGradient::setGradient(VGradient gradient)
{
    m_gradient = gradient;
    m_mode = gradient.type();
    changeUI();
}

void ColorPickerGradient::changeSize()
{
    adjustSize();
    emit sizeChanged();
}
