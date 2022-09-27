#include "colorpicker_gradient.h"
#include "icon_manager.h"
#include "ui_colorpicker_gradient.h"
#include "popup_menu/popup_menu.h"
#include "enums.h"
//#include <QElapsedTimer>

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

ColorPickerGradient::ColorPickerGradient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorPickerGradient)
{
    //    QElapsedTimer timer;
    //    timer.start();
    //    qDebug() << "ColorPicker Gradient start" << timer.elapsed() << "ms";

    ui->setupUi(this);

    setWindowTitle(tr("Edit Gradient"));

    setup();
    connectSlots();

    //   qDebug() << "ColorPicker Gradient initialize in" << timer.elapsed() << "ms";
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
    ui->sectionGradient->addHeaderSuffixWidget(ui->comboType);
    ui->sectionSwatches->setCollapseIcons(iconCollapsed, iconOpen);

    // Buttons
    ui->buttonAddGradient->setIcon(iconManager.icon("add"));

    // Picker Type
    ui->comboType->addItem(tr("Linear"),        QVariant::fromValue(GradientType::Linear));
    ui->comboType->addItem(tr("Radial"),        QVariant::fromValue(GradientType::Radial));
    ui->comboType->addItem(tr("Conical"),       QVariant::fromValue(GradientType::Conical));
    ui->comboType->addItem(tr("Diamond"),       QVariant::fromValue(GradientType::Diamond));
    ui->comboType->addItem(tr("4 Colors"),      QVariant::fromValue(GradientType::FourColors));
    ui->comboType->addItem(tr("Mesh"),          QVariant::fromValue(GradientType::Mesh));
    ui->comboType->addItem(tr("Patch Mesh"),    QVariant::fromValue(GradientType::PatchMesh));

    // Color Buttons
    ui->buttonColor->setConfiguration(ColorPickerConfig::Text);
    ui->buttonColor->setColorPickerType(ColorButton::ColorPickerSolid);
    ui->buttonMeshNode->setConfiguration(ColorPickerConfig::Text);
    ui->buttonMeshNode->setColorPickerType(ColorButton::ColorPickerSolid);
    ui->button4CTopLeft->setConfiguration(ColorPickerConfig::Text);
    ui->button4CTopLeft->setColorPickerType(ColorButton::ColorPickerSolid);
    ui->button4CTopRight->setConfiguration(ColorPickerConfig::Text);
    ui->button4CTopRight->setColorPickerType(ColorButton::ColorPickerSolid);
    ui->button4CBottomLeft->setConfiguration(ColorPickerConfig::Text);
    ui->button4CBottomLeft->setColorPickerType(ColorButton::ColorPickerSolid);
    ui->button4CBottomRight->setConfiguration(ColorPickerConfig::Text);
    ui->button4CBottomRight->setColorPickerType(ColorButton::ColorPickerSolid);


    // Swatches
    ui->swatches->setConfiguration(ItemFillMode::Gradient);

    // Default Values
    ScColor baseGradient = ui->gradientEdit->gradient().colorStops().first()->color;
    ui->buttonColor->setColor(baseGradient);

}

void ColorPickerGradient::connectSlots()
{

    connect(ui->comboType,              &QComboBox::currentIndexChanged, this, &ColorPickerGradient::changeSelectorMode);

    connect(ui->gradientEdit,           &GradientEdit::selectedColor, this, &ColorPickerGradient::updateGradientColor);
    connect(ui->gradientEdit,           &GradientEdit::selectedPosition, this, &ColorPickerGradient::updateSimpleGradientInputPosition);

    connect(ui->numberPosition,         &QSpinBox::valueChanged, this, &ColorPickerGradient::updateSimpleGradientStep);

    connect(ui->buttonColor,            &ColorButton::colorChanged, this, &ColorPickerGradient::updateGradientColor);
    connect(ui->buttonMeshNode,         &ColorButton::colorChanged, this, &ColorPickerGradient::updateGradientColor);
    connect(ui->button4CTopLeft,        &ColorButton::colorChanged, this, &ColorPickerGradient::updateGradientColor);
    connect(ui->button4CTopRight,       &ColorButton::colorChanged, this, &ColorPickerGradient::updateGradientColor);
    connect(ui->button4CBottomLeft,     &ColorButton::colorChanged, this, &ColorPickerGradient::updateGradientColor);
    connect(ui->button4CBottomRight,    &ColorButton::colorChanged, this, &ColorPickerGradient::updateGradientColor);

    // Sections
    connect(ui->sectionGradient,        &SectionContainer::collapsedState, this, &ColorPickerGradient::changeSize);
    connect(ui->sectionSwatches,        &SectionContainer::collapsedState, this, &ColorPickerGradient::changeSize);

}

void ColorPickerGradient::disconnectSlots()
{
    disconnect(ui->comboType,           &QComboBox::currentIndexChanged, this, &ColorPickerGradient::changeSelectorMode);

    disconnect(ui->gradientEdit,        &GradientEdit::selectedColor, this, &ColorPickerGradient::updateGradientColor);
    disconnect(ui->gradientEdit,        &GradientEdit::selectedPosition, this, &ColorPickerGradient::updateSimpleGradientInputPosition);

    disconnect(ui->numberPosition,      &QSpinBox::valueChanged, this, &ColorPickerGradient::updateSimpleGradientStep);

    disconnect(ui->buttonColor,         &ColorButton::colorChanged, this, &ColorPickerGradient::updateGradientColor);
    disconnect(ui->buttonMeshNode,      &ColorButton::colorChanged, this, &ColorPickerGradient::updateGradientColor);
    disconnect(ui->button4CTopLeft,     &ColorButton::colorChanged, this, &ColorPickerGradient::updateGradientColor);
    disconnect(ui->button4CTopRight,    &ColorButton::colorChanged, this, &ColorPickerGradient::updateGradientColor);
    disconnect(ui->button4CBottomLeft,  &ColorButton::colorChanged, this, &ColorPickerGradient::updateGradientColor);
    disconnect(ui->button4CBottomRight, &ColorButton::colorChanged, this, &ColorPickerGradient::updateGradientColor);

    // Sections
    disconnect(ui->sectionGradient,     &SectionContainer::collapsedState, this, &ColorPickerGradient::changeSize);
    disconnect(ui->sectionSwatches,     &SectionContainer::collapsedState, this, &ColorPickerGradient::changeSize);

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
        ui->comboType->addItem(tr("Linear"),        QVariant::fromValue(GradientType::Linear));
        ui->comboType->addItem(tr("Radial"),        QVariant::fromValue(GradientType::Radial));
        ui->comboType->setCurrentIndex(0);
        break;

    case ColorPickerConfig::Fill:
        ui->comboType->addItem(tr("Linear"),        QVariant::fromValue(GradientType::Linear));
        ui->comboType->addItem(tr("Radial"),        QVariant::fromValue(GradientType::Radial));
        ui->comboType->addItem(tr("Conical"),       QVariant::fromValue(GradientType::Conical));
        ui->comboType->addItem(tr("Diamond"),       QVariant::fromValue(GradientType::Diamond));
        ui->comboType->addItem(tr("4 Colors"),      QVariant::fromValue(GradientType::FourColors));
        ui->comboType->addItem(tr("Mesh"),          QVariant::fromValue(GradientType::Mesh));
        ui->comboType->addItem(tr("Patch Mesh"),    QVariant::fromValue(GradientType::PatchMesh));
        ui->comboType->setCurrentIndex(0);
        break;
    case ColorPickerConfig::StrokeMask:
    case ColorPickerConfig::Text:
    case ColorPickerConfig::Shadow:
    case ColorPickerConfig::Default:

        break;
    }

    connectSlots();

    // set right mode after combobox reset
    m_mode = static_cast<GradientType>(ui->comboType->currentData(Qt::UserRole).toInt());
    changeUI();
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

        // Add colors clockwise
        VGradient gradient4Color(GradientType::FourColors);
        gradient4Color.clearStops(); // delete default stops

        ScColor col = ui->button4CTopLeft->color();
        gradient4Color.addStop(col, .0, .5, col.alphaF(), col.name());
        col = ui->button4CTopRight->color();
        gradient4Color.addStop(col, 1. / 3, .5, col.alphaF(), col.name());
        col = ui->button4CBottomRight->color();
        gradient4Color.addStop(col, 1. / 3 * 2, .5, col.alphaF(), col.name());
        col = ui->button4CBottomLeft->color();
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

void ColorPickerGradient::updateGradientControls()
{
    switch(m_mode){
    default:
    case GradientType::Linear:
    case GradientType::Radial:
    case GradientType::Conical:
    case GradientType::Diamond:

        ui->gradientEdit->setGradient(m_gradient);
        ui->buttonColor->setColor(ui->gradientEdit->activeStopColor());

        break;
    case GradientType::FourColors:{

        int size = m_gradient.colorStops().size();

        // Get color clockwise
        if( size > 0 ){
            ui->button4CTopLeft->setColor(m_gradient.colorStops().at(0)->color);
        }
        if( size > 1 ){
            ui->button4CTopRight->setColor(m_gradient.colorStops().at(1)->color);
        }
        if( size > 2 ){
            ui->button4CBottomRight->setColor(m_gradient.colorStops().at(2)->color);
        }
        if( size > 3 ){
            ui->button4CBottomLeft->setColor(m_gradient.colorStops().at(3)->color);
        }


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

    disconnectSlots();
    updateGradientControls();
    connectSlots();

    changeUI();
    createGradient();
    emit gradientChanged(m_gradient);
}


void ColorPickerGradient::updateGradientColor(ScColor color)
{

    if( ui->gradientEdit  != qobject_cast<GradientEdit*>(sender()) ) ui->gradientEdit->setActiveStopColor(color);
    if( ui->gradientEdit  == qobject_cast<GradientEdit*>(sender()) ) ui->buttonColor->setColor(color);


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

    GradientType gradType = gradient.type();
    int index = ui->comboType->findData(QVariant::fromValue(gradType));

    if ( index != -1 ) {
        ui->comboType->setCurrentIndex(index);
        m_mode = gradType;
    }

    disconnectSlots();
    updateGradientControls();
    changeUI();
    connectSlots();
}

void ColorPickerGradient::changeSize()
{
    adjustSize();
    emit sizeChanged();
}
