#include "colorpicker_color.h"
#include "colorblind.h"
#include "eyedropper_widget.h"
#include "ui_colorpicker_color.h"

#include "icon_manager.h"
#include "render_utils.h"
#include <QAction>
#include <QMenu>
#include <QMouseEvent>

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

ColorPickerColor::ColorPickerColor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorPickerColor)
{
    ui->setupUi(this);

    setWindowTitle(tr("Edit Color"));
    setWindowFlag(Qt::WindowMinMaxButtonsHint, false);
    setup();

    // Setup default states
    switchSliderScale(actionSliderScale->isChecked());
    setColor(ScColor(255,0,0));

}

ColorPickerColor::ColorPickerColor(ColorPickerConfig config, QWidget *parent) : ColorPickerColor(parent)
{
    setConfiguration(config);
}

ColorPickerColor::~ColorPickerColor()
{
    delete ui;
}


void ColorPickerColor::setup()
{
    IconManager & iconManager = IconManager::instance();

    QIcon iconCollapsed = iconManager.icon("chevron-right");
    QIcon iconOpen = iconManager.icon("chevron-down");

    eyeDropper = new EyeDropperWidget(this);

    // Values
    m_colorSpace = ColorModel::HSV;
    m_defectMode = VisionDefectColor::normalVision;
    m_colorMapMode = ColorMap::HSVHue;
    m_harmony = ColorHarmonyWheel::Complementary;
    m_pickerMode = PickerMode::Map;


    // Buttons
    ui->buttonAddColor->setIcon(iconManager.icon("add"));
    ui->buttonEyeDropper->setIcon(iconManager.icon("eyedropper"));
    ui->buttonSettings->setIcon(iconManager.icon("setting-edit"));
    ui->buttonSpotColor->setIcon(iconManager.icon("color-spot"));

    // Picker Button
    buttonPickerToggle = new QToolButton();
    buttonPickerToggle->setPopupMode(QToolButton::InstantPopup);

    // Color Space Combobox
    comboColorSpace = new QComboBox();

    // Spot Button
    ui->buttonSpotColor->setToolTip(tr("Toggle if color is spot color."));

    // Stacks
    ui->stackSlider->setCurrentIndex(0);
    ui->stackPicker->setCurrentIndex(0);

    // Sections
    ui->sectionPicker->setCollapseIcons(iconCollapsed, iconOpen);
    ui->sectionPicker->addHeaderWidget(comboColorSpace);
    ui->sectionPicker->addHeaderWidget(buttonPickerToggle);
    ui->sectionSwatches->setCollapseIcons(iconCollapsed, iconOpen);


    // Color Buttons
    ui->buttonColor1->setVisible(true);
    ui->buttonColor2->setVisible(false);
    ui->buttonColor3->setVisible(false);
    ui->buttonColor4->setVisible(false);


    // Color Space
    comboColorSpace->addItem("HSV", QVariant::fromValue(ColorModel::HSV));
    comboColorSpace->addItem("RGB", QVariant::fromValue(ColorModel::RGB));
    comboColorSpace->addItem("CMYK", QVariant::fromValue(ColorModel::CMYK));
    comboColorSpace->addItem("Lab", QVariant::fromValue(ColorModel::Lab));

    // Picker
    actionPickerMap      = new QAction(iconManager.icon("colorpicker-map"), "Map", this);
    actionPickerHarmony = new QAction(iconManager.icon("colorpicker-harmony"), "Harmony", this);

    actionPickerMap->setData(PickerMode::Map);
    actionPickerHarmony->setData(PickerMode::Harmony);

    menuPicker = new QMenu;
    menuPicker->addAction(actionPickerMap);
    menuPicker->addAction(actionPickerHarmony);

    buttonPickerToggle->setMenu(menuPicker);
    buttonPickerToggle->setDefaultAction(actionPickerMap);


    // Color Harmony
    ui->colorHarmonyWheel->setHarmony(m_harmony);
    ui->sliderHarmonyValue->setMode(ColorSlider::HSVValue);

    actionHarmonyComplementary      = new QAction(iconManager.icon("harmony-complementary"), "Complementary", this);
    actionHarmonySplitComplementary = new QAction(iconManager.icon("harmony-split-complementary"), "Split Complementary", this);
    actionHarmonyTriadic            = new QAction(iconManager.icon("harmony-triadic"), "Triadic", this);
    actionHarmonyTetradic           = new QAction(iconManager.icon("harmony-tetradic"), "Tetradic", this);
    actionHarmonySquare             = new QAction(iconManager.icon("harmony-square"), "Square", this);
    actionHarmonyAnalogous          = new QAction(iconManager.icon("harmony-analogous"), "Analogous", this);
    actionHarmonyMonochromatic      = new QAction(iconManager.icon("harmony-monochromatic"), "Monochromatic", this);

    actionHarmonyComplementary->setData(ColorHarmonyWheel::Complementary);
    actionHarmonySplitComplementary->setData(ColorHarmonyWheel::SplitComplementary);
    actionHarmonyTriadic->setData(ColorHarmonyWheel::Triadic);
    actionHarmonyTetradic->setData(ColorHarmonyWheel::Tetradic);
    actionHarmonySquare->setData(ColorHarmonyWheel::Square);
    actionHarmonyAnalogous->setData(ColorHarmonyWheel::Analogous);
    actionHarmonyMonochromatic->setData(ColorHarmonyWheel::Monochromatic);

    menuHarmony = new QMenu;
    menuHarmony->addAction(actionHarmonyComplementary);
    menuHarmony->addAction(actionHarmonySplitComplementary);
    menuHarmony->addAction(actionHarmonyTriadic);
    menuHarmony->addAction(actionHarmonyTetradic);
    menuHarmony->addAction(actionHarmonySquare);
    menuHarmony->addAction(actionHarmonyAnalogous);
    menuHarmony->addAction(actionHarmonyMonochromatic);

    ui->buttonHarmony->setMenu(menuHarmony);
    ui->buttonHarmony->setDefaultAction(actionHarmonyComplementary);


    // Color Slider
    ui->sliderCMYKCyan->setMode(ColorSlider::CMYKCyan);
    ui->sliderCMYKMagenta->setMode(ColorSlider::CMYKMagenta);
    ui->sliderCMYKYellow->setMode(ColorSlider::CMYKYellow);
    ui->sliderCMYKKey->setMode(ColorSlider::CMYKKey);

    ui->sliderRGBRed->setMode(ColorSlider::RGBRed);
    ui->sliderRGBGreen->setMode(ColorSlider::RGBGreen);
    ui->sliderRGBBlue->setMode(ColorSlider::RGBBlue);

    ui->sliderHSVHue->setMode(ColorSlider::HSVHue);
    ui->sliderHSVSaturation->setMode(ColorSlider::HSVSaturation);
    ui->sliderHSVValue->setMode(ColorSlider::HSVValue);

    ui->sliderLabL->setMode(ColorSlider::LabLightness);
    ui->sliderLabA->setMode(ColorSlider::LabA);
    ui->sliderLabB->setMode(ColorSlider::LabB);

    ui->sliderAlpha->setMode(ColorSlider::Alpha);
    ui->sliderShade->setMode(ColorSlider::Shade);


    // Numeric Inputs
    ui->numberCMYKCyan->setValue(ui->sliderCMYKCyan->value());
    ui->numberCMYKMagenta->setValue(ui->sliderCMYKMagenta->value());
    ui->numberCMYKYellow->setValue(ui->sliderCMYKYellow->value());
    ui->numberCMYKKey->setValue(ui->sliderCMYKKey->value());
    ui->numberRGBRed->setValue(ui->sliderRGBRed->value());
    ui->numberRGBGreen->setValue(ui->sliderRGBGreen->value());
    ui->numberRGBBlue->setValue(ui->sliderRGBBlue->value());
    ui->numberHSVHue->setValue(ui->sliderHSVHue->value());
    ui->numberHSVSaturation->setValue(ui->sliderHSVSaturation->value());
    ui->numberHSVValue->setValue(ui->sliderHSVValue->value());
    ui->numberLabL->setValue(ui->sliderLabL->value());
    ui->numberLabA->setValue(ui->sliderLabA->value());
    ui->numberLabB->setValue(ui->sliderLabB->value());
    ui->numberAlpha->setValue(ui->sliderAlpha->value());
    ui->numberShade->setValue(ui->sliderShade->value());


    // Color Blindness
    actionColorBlindNormal  = new QAction(iconManager.icon("colorblind-normal"), "Normal Vision", this);
    actionColorBlindRed     = new QAction(iconManager.icon("colorblind-red"), "Protanopia (Red)", this);
    actionColorBlindGreen   = new QAction(iconManager.icon("colorblind-green"), "Deuteranopia (Green)", this);
    actionColorBlindBlue    = new QAction(iconManager.icon("colorblind-blue"), "Tritanopia (Blue)", this);
    actionColorBlindFull    = new QAction(iconManager.icon("colorblind-full"), "Full Color Blindness", this);

    actionColorBlindNormal->setData(VisionDefectColor::normalVision);
    actionColorBlindRed->setData(VisionDefectColor::protanopeVision);
    actionColorBlindGreen->setData(VisionDefectColor::deuteranopeVision);
    actionColorBlindBlue->setData(VisionDefectColor::tritanopeVision);
    actionColorBlindFull->setData(VisionDefectColor::colorBlindnessVision);

    menuColorBlind = new QMenu;
    menuColorBlind->addAction(actionColorBlindNormal);
    menuColorBlind->addAction(actionColorBlindRed);
    menuColorBlind->addAction(actionColorBlindGreen);
    menuColorBlind->addAction(actionColorBlindBlue);
    menuColorBlind->addAction(actionColorBlindFull);

    ui->buttonColorBlind->setMenu(menuColorBlind);
    ui->buttonColorBlind->setDefaultAction(actionColorBlindNormal);

    // Color Map
    ui->colorMap->setMode(ColorMap::HSVHue);
    ui->sliderUniversal->setMode(ColorSlider::HSVValue);

    // Color Map Mode
    actionMapHSVHue         = new QAction(iconManager.icon("color-map-mode"), "Hue", this);
    actionMapHSVSaturation  = new QAction(iconManager.icon("color-map-mode"), "Saturation", this);
    actionMapHSVValue       = new QAction(iconManager.icon("color-map-mode"), "Value", this);
    actionMapRGBRed         = new QAction(iconManager.icon("color-map-mode"), "Red", this);
    actionMapRGBGreen       = new QAction(iconManager.icon("color-map-mode"), "Green", this);
    actionMapRGBBlue        = new QAction(iconManager.icon("color-map-mode"), "Blue", this);
    actionMapLabL           = new QAction(iconManager.icon("color-map-mode"), "Lightness", this);
    actionMapLaba           = new QAction(iconManager.icon("color-map-mode"), "a", this);
    actionMapLabb           = new QAction(iconManager.icon("color-map-mode"), "b", this);

    actionMapHSVHue->setData(ColorMap::HSVHue);
    actionMapHSVSaturation->setData(ColorMap::HSVSaturation);
    actionMapHSVValue->setData(ColorMap::HSVValue);
    actionMapRGBRed->setData(ColorMap::RGBRed);
    actionMapRGBGreen->setData(ColorMap::RGBGreen);
    actionMapRGBBlue->setData(ColorMap::RGBBlue);
    actionMapLabL->setData(ColorMap::LabLightness);
    actionMapLaba->setData(ColorMap::LabA);
    actionMapLabb->setData(ColorMap::LabB);

    menuMapMode = new QMenu;
    menuMapMode->addAction(actionMapHSVHue);
    menuMapMode->addAction(actionMapHSVSaturation);
    menuMapMode->addAction(actionMapHSVValue);
    menuMapMode->addSeparator();
    menuMapMode->addAction(actionMapRGBRed);
    menuMapMode->addAction(actionMapRGBGreen);
    menuMapMode->addAction(actionMapRGBBlue);
    menuMapMode->addSeparator();
    menuMapMode->addAction(actionMapLabL);
    menuMapMode->addAction(actionMapLaba);
    menuMapMode->addAction(actionMapLabb);

    ui->buttonMapMode->setMenu(menuMapMode);
    ui->buttonMapMode->setDefaultAction(actionMapHSVHue);


    // Settings
    actionColorBlind = new QAction("Color Blind Mode", this);
    actionColorBlind->setCheckable(true);
    actionColorBlind->setChecked(true);

    actionSliderScale = new QAction("Slider Scale", this);
    actionSliderScale->setCheckable(true);
    actionSliderScale->setChecked(false);

    menuSettings = new QMenu;
    menuSettings->addAction(actionColorBlind);
    menuSettings->addAction(actionSliderScale);

    ui->buttonSettings->setMenu(menuSettings);


    // Swatches
    ui->swatches->setConfiguration(ItemFillMode::Solid);


    // Connections
    connectSlots();

}

void ColorPickerColor::connectSlots()
{

    // ComboBoxes
    connect(comboColorSpace,    &QComboBox::currentIndexChanged, this, &ColorPickerColor::changeColorSpace);

    // Map
    connect(ui->colorMap,           &ColorMap::colorChanged, this, &ColorPickerColor::changeColor);
    connect(ui->buttonMapMode,      &QToolButton::triggered, ui->buttonMapMode, &QToolButton::setDefaultAction);
    connect(ui->sliderUniversal,    &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    connect(actionMapHSVHue,        &QAction::triggered,this, &ColorPickerColor::changeMapMode );
    connect(actionMapHSVSaturation, &QAction::triggered,this, &ColorPickerColor::changeMapMode );
    connect(actionMapHSVValue,      &QAction::triggered,this, &ColorPickerColor::changeMapMode );
    connect(actionMapRGBRed,        &QAction::triggered,this, &ColorPickerColor::changeMapMode );
    connect(actionMapRGBGreen,      &QAction::triggered,this, &ColorPickerColor::changeMapMode );
    connect(actionMapRGBBlue,       &QAction::triggered,this, &ColorPickerColor::changeMapMode );
    connect(actionMapLabL,          &QAction::triggered,this, &ColorPickerColor::changeMapMode );
    connect(actionMapLaba,          &QAction::triggered,this, &ColorPickerColor::changeMapMode );
    connect(actionMapLabb,          &QAction::triggered,this, &ColorPickerColor::changeMapMode );

    // Slider (color)
    connect(ui->sliderCMYKCyan,         &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    connect(ui->sliderCMYKMagenta,      &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    connect(ui->sliderCMYKYellow,       &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    connect(ui->sliderCMYKKey,          &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    connect(ui->sliderRGBRed,           &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    connect(ui->sliderRGBGreen,         &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    connect(ui->sliderRGBBlue,          &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    connect(ui->sliderHSVHue,           &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    connect(ui->sliderHSVSaturation,    &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    connect(ui->sliderHSVValue,         &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    connect(ui->sliderLabL,             &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    connect(ui->sliderLabA,             &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    connect(ui->sliderLabB,             &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    connect(ui->sliderAlpha,            &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    connect(ui->sliderShade,            &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);

    // Slider (value)
    connect(ui->sliderCMYKCyan,         &ColorSlider::valueChanged, ui->numberCMYKCyan, &QDoubleSpinBox::setValue);
    connect(ui->sliderCMYKMagenta,      &ColorSlider::valueChanged, ui->numberCMYKMagenta, &QDoubleSpinBox::setValue);
    connect(ui->sliderCMYKYellow,       &ColorSlider::valueChanged, ui->numberCMYKYellow, &QDoubleSpinBox::setValue);
    connect(ui->sliderCMYKKey,          &ColorSlider::valueChanged, ui->numberCMYKKey, &QDoubleSpinBox::setValue);
    connect(ui->sliderRGBRed,           &ColorSlider::valueChanged, ui->numberRGBRed, &QDoubleSpinBox::setValue);
    connect(ui->sliderRGBGreen,         &ColorSlider::valueChanged, ui->numberRGBGreen, &QDoubleSpinBox::setValue);
    connect(ui->sliderRGBBlue,          &ColorSlider::valueChanged, ui->numberRGBBlue, &QDoubleSpinBox::setValue);
    connect(ui->sliderHSVHue,           &ColorSlider::valueChanged, ui->numberHSVHue, &QDoubleSpinBox::setValue);
    connect(ui->sliderHSVSaturation,    &ColorSlider::valueChanged, ui->numberHSVSaturation, &QDoubleSpinBox::setValue);
    connect(ui->sliderHSVValue,         &ColorSlider::valueChanged, ui->numberHSVValue, &QDoubleSpinBox::setValue);
    connect(ui->sliderLabL,             &ColorSlider::valueChanged, ui->numberLabL, &QDoubleSpinBox::setValue);
    connect(ui->sliderLabA,             &ColorSlider::valueChanged, ui->numberLabA, &QDoubleSpinBox::setValue);
    connect(ui->sliderLabB,             &ColorSlider::valueChanged, ui->numberLabB, &QDoubleSpinBox::setValue);
    connect(ui->sliderAlpha,            &ColorSlider::valueChanged, ui->numberAlpha, &QDoubleSpinBox::setValue);
    connect(ui->sliderShade,            &ColorSlider::valueChanged, ui->numberShade, &QDoubleSpinBox::setValue);

    // Inputs (slider)
    connect(ui->numberCMYKCyan,         &QDoubleSpinBox::valueChanged, ui->sliderCMYKCyan, &ColorSlider::setValue);
    connect(ui->numberCMYKMagenta,      &QDoubleSpinBox::valueChanged, ui->sliderCMYKMagenta, &ColorSlider::setValue);
    connect(ui->numberCMYKYellow,       &QDoubleSpinBox::valueChanged, ui->sliderCMYKYellow, &ColorSlider::setValue);
    connect(ui->numberCMYKKey,          &QDoubleSpinBox::valueChanged, ui->sliderCMYKKey, &ColorSlider::setValue);
    connect(ui->numberRGBRed,           &QDoubleSpinBox::valueChanged, ui->sliderRGBRed, &ColorSlider::setValue);
    connect(ui->numberRGBGreen,         &QDoubleSpinBox::valueChanged, ui->sliderRGBGreen, &ColorSlider::setValue);
    connect(ui->numberRGBBlue,          &QDoubleSpinBox::valueChanged, ui->sliderRGBBlue, &ColorSlider::setValue);
    connect(ui->numberHSVHue,           &QDoubleSpinBox::valueChanged, ui->sliderHSVHue, &ColorSlider::setValue);
    connect(ui->numberHSVSaturation,    &QDoubleSpinBox::valueChanged, ui->sliderHSVSaturation, &ColorSlider::setValue);
    connect(ui->numberHSVValue,         &QDoubleSpinBox::valueChanged, ui->sliderHSVValue, &ColorSlider::setValue);
    connect(ui->numberLabL,             &QDoubleSpinBox::valueChanged, ui->sliderLabL, &ColorSlider::setValue);
    connect(ui->numberLabA,             &QDoubleSpinBox::valueChanged, ui->sliderLabA, &ColorSlider::setValue);
    connect(ui->numberLabB,             &QDoubleSpinBox::valueChanged, ui->sliderLabB, &ColorSlider::setValue);
    connect(ui->numberAlpha,            &QDoubleSpinBox::valueChanged, ui->sliderAlpha, &ColorSlider::setValue);
    connect(ui->numberShade,            &QDoubleSpinBox::valueChanged, ui->sliderShade, &ColorSlider::setValue);

    // Color Harmony
    connect(ui->sliderHarmonyValue, &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    connect(ui->colorHarmonyWheel,  &ColorHarmonyWheel::colorChanged, this, &ColorPickerColor::changeColor);
    connect(ui->colorHarmonyWheel,  &ColorHarmonyWheel::harmonyChanged, this, &ColorPickerColor::changeColorButtons);
    connect(ui->buttonHarmony,      &QToolButton::triggered, ui->buttonHarmony, &QToolButton::setDefaultAction);
    connect(actionHarmonyAnalogous,             &QAction::triggered,this, &ColorPickerColor::changeHarmony );
    connect(actionHarmonyComplementary,         &QAction::triggered,this, &ColorPickerColor::changeHarmony );
    connect(actionHarmonyMonochromatic,         &QAction::triggered,this, &ColorPickerColor::changeHarmony );
    connect(actionHarmonySplitComplementary,    &QAction::triggered,this, &ColorPickerColor::changeHarmony );
    connect(actionHarmonySquare,                &QAction::triggered,this, &ColorPickerColor::changeHarmony );
    connect(actionHarmonyTetradic,              &QAction::triggered,this, &ColorPickerColor::changeHarmony );
    connect(actionHarmonyTriadic,               &QAction::triggered,this, &ColorPickerColor::changeHarmony );

    // Color Blindness
    connect(ui->buttonColorBlind,   &QToolButton::triggered, ui->buttonColorBlind, &QToolButton::setDefaultAction);
    connect(actionColorBlindNormal, &QAction::triggered,this, &ColorPickerColor::changeColorBlindness );
    connect(actionColorBlindRed,    &QAction::triggered,this, &ColorPickerColor::changeColorBlindness );
    connect(actionColorBlindGreen,  &QAction::triggered,this, &ColorPickerColor::changeColorBlindness );
    connect(actionColorBlindBlue,   &QAction::triggered,this, &ColorPickerColor::changeColorBlindness );
    connect(actionColorBlindFull,   &QAction::triggered,this, &ColorPickerColor::changeColorBlindness );

    // Color Buttons
    connect(ui->buttonColorMain,    &QToolButton::pressed, this, &ColorPickerColor::changeHarmonyColor );
    connect(ui->buttonColor1,       &QToolButton::pressed, this, &ColorPickerColor::changeHarmonyColor );
    connect(ui->buttonColor2,       &QToolButton::pressed, this, &ColorPickerColor::changeHarmonyColor );
    connect(ui->buttonColor3,       &QToolButton::pressed, this, &ColorPickerColor::changeHarmonyColor );
    connect(ui->buttonColor4,       &QToolButton::pressed, this, &ColorPickerColor::changeHarmonyColor );

    // Settings
    connect(actionColorBlind,       &QAction::toggled,this, &ColorPickerColor::switchColorBlind );
    connect(actionSliderScale,      &QAction::toggled,this, &ColorPickerColor::switchSliderScale );

    // Color Swatches
    connect(ui->swatches,           &ColorSwatches::colorChanged, this, &ColorPickerColor::setColorFromSwatch);


    // Sections
    connect(ui->sectionPicker,      &SectionContainer::collapsedState, this, &ColorPickerColor::changeSize);
    connect(ui->sectionSwatches,    &SectionContainer::collapsedState, this, &ColorPickerColor::changeSize);

    // Picker Button
    connect(buttonPickerToggle,     &QToolButton::triggered, buttonPickerToggle, &QToolButton::setDefaultAction);
    connect(actionPickerMap,        &QAction::triggered,this, &ColorPickerColor::changePickerMode );
    connect(actionPickerHarmony,    &QAction::triggered,this, &ColorPickerColor::changePickerMode );

    // Spot Button
    connect(ui->buttonSpotColor,    &QToolButton::toggled, this, &ColorPickerColor::setSpotFlag);

    // EyeDroper
    connect(ui->buttonEyeDropper,   &QToolButton::released, eyeDropper, &EyeDropperWidget::show);
    connect(eyeDropper,             &EyeDropperWidget::screenColor, this, &ColorPickerColor::changeColor);


}

void ColorPickerColor::disconnectSlots()
{
    // ComboBoxes
    disconnect(comboColorSpace,    &QComboBox::currentIndexChanged, this, &ColorPickerColor::changeColorSpace);

    // Map
    disconnect(ui->colorMap,           &ColorMap::colorChanged, this, &ColorPickerColor::changeColor);
    disconnect(ui->buttonMapMode,      &QToolButton::triggered, ui->buttonMapMode, &QToolButton::setDefaultAction);
    disconnect(ui->sliderUniversal,    &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    disconnect(actionMapHSVHue,        &QAction::triggered,this, &ColorPickerColor::changeMapMode );
    disconnect(actionMapHSVSaturation, &QAction::triggered,this, &ColorPickerColor::changeMapMode );
    disconnect(actionMapHSVValue,      &QAction::triggered,this, &ColorPickerColor::changeMapMode );
    disconnect(actionMapRGBRed,        &QAction::triggered,this, &ColorPickerColor::changeMapMode );
    disconnect(actionMapRGBGreen,      &QAction::triggered,this, &ColorPickerColor::changeMapMode );
    disconnect(actionMapRGBBlue,       &QAction::triggered,this, &ColorPickerColor::changeMapMode );
    disconnect(actionMapLabL,          &QAction::triggered,this, &ColorPickerColor::changeMapMode );
    disconnect(actionMapLaba,          &QAction::triggered,this, &ColorPickerColor::changeMapMode );
    disconnect(actionMapLabb,          &QAction::triggered,this, &ColorPickerColor::changeMapMode );

    // Slider (color)
    disconnect(ui->sliderCMYKCyan,         &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    disconnect(ui->sliderCMYKMagenta,      &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    disconnect(ui->sliderCMYKYellow,       &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    disconnect(ui->sliderCMYKKey,          &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    disconnect(ui->sliderRGBRed,           &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    disconnect(ui->sliderRGBGreen,         &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    disconnect(ui->sliderRGBBlue,          &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    disconnect(ui->sliderHSVHue,           &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    disconnect(ui->sliderHSVSaturation,    &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    disconnect(ui->sliderHSVValue,         &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    disconnect(ui->sliderLabL,             &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    disconnect(ui->sliderLabA,             &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    disconnect(ui->sliderLabB,             &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    disconnect(ui->sliderAlpha,            &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    disconnect(ui->sliderShade,            &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);

    // Slider (value)
    disconnect(ui->sliderCMYKCyan,         &ColorSlider::valueChanged, ui->numberCMYKCyan, &QDoubleSpinBox::setValue);
    disconnect(ui->sliderCMYKMagenta,      &ColorSlider::valueChanged, ui->numberCMYKMagenta, &QDoubleSpinBox::setValue);
    disconnect(ui->sliderCMYKYellow,       &ColorSlider::valueChanged, ui->numberCMYKYellow, &QDoubleSpinBox::setValue);
    disconnect(ui->sliderCMYKKey,          &ColorSlider::valueChanged, ui->numberCMYKKey, &QDoubleSpinBox::setValue);
    disconnect(ui->sliderRGBRed,           &ColorSlider::valueChanged, ui->numberRGBRed, &QDoubleSpinBox::setValue);
    disconnect(ui->sliderRGBGreen,         &ColorSlider::valueChanged, ui->numberRGBGreen, &QDoubleSpinBox::setValue);
    disconnect(ui->sliderRGBBlue,          &ColorSlider::valueChanged, ui->numberRGBBlue, &QDoubleSpinBox::setValue);
    disconnect(ui->sliderHSVHue,           &ColorSlider::valueChanged, ui->numberHSVHue, &QDoubleSpinBox::setValue);
    disconnect(ui->sliderHSVSaturation,    &ColorSlider::valueChanged, ui->numberHSVSaturation, &QDoubleSpinBox::setValue);
    disconnect(ui->sliderHSVValue,         &ColorSlider::valueChanged, ui->numberHSVValue, &QDoubleSpinBox::setValue);
    disconnect(ui->sliderLabL,             &ColorSlider::valueChanged, ui->numberLabL, &QDoubleSpinBox::setValue);
    disconnect(ui->sliderLabA,             &ColorSlider::valueChanged, ui->numberLabA, &QDoubleSpinBox::setValue);
    disconnect(ui->sliderLabB,             &ColorSlider::valueChanged, ui->numberLabB, &QDoubleSpinBox::setValue);
    disconnect(ui->sliderAlpha,            &ColorSlider::valueChanged, ui->numberAlpha, &QDoubleSpinBox::setValue);
    disconnect(ui->sliderShade,            &ColorSlider::valueChanged, ui->numberShade, &QDoubleSpinBox::setValue);

    // Inputs (slider)
    disconnect(ui->numberCMYKCyan,         &QDoubleSpinBox::valueChanged, ui->sliderCMYKCyan, &ColorSlider::setValue);
    disconnect(ui->numberCMYKMagenta,      &QDoubleSpinBox::valueChanged, ui->sliderCMYKMagenta, &ColorSlider::setValue);
    disconnect(ui->numberCMYKYellow,       &QDoubleSpinBox::valueChanged, ui->sliderCMYKYellow, &ColorSlider::setValue);
    disconnect(ui->numberCMYKKey,          &QDoubleSpinBox::valueChanged, ui->sliderCMYKKey, &ColorSlider::setValue);
    disconnect(ui->numberRGBRed,           &QDoubleSpinBox::valueChanged, ui->sliderRGBRed, &ColorSlider::setValue);
    disconnect(ui->numberRGBGreen,         &QDoubleSpinBox::valueChanged, ui->sliderRGBGreen, &ColorSlider::setValue);
    disconnect(ui->numberRGBBlue,          &QDoubleSpinBox::valueChanged, ui->sliderRGBBlue, &ColorSlider::setValue);
    disconnect(ui->numberHSVHue,           &QDoubleSpinBox::valueChanged, ui->sliderHSVHue, &ColorSlider::setValue);
    disconnect(ui->numberHSVSaturation,    &QDoubleSpinBox::valueChanged, ui->sliderHSVSaturation, &ColorSlider::setValue);
    disconnect(ui->numberHSVValue,         &QDoubleSpinBox::valueChanged, ui->sliderHSVValue, &ColorSlider::setValue);
    disconnect(ui->numberLabL,             &QDoubleSpinBox::valueChanged, ui->sliderLabL, &ColorSlider::setValue);
    disconnect(ui->numberLabA,             &QDoubleSpinBox::valueChanged, ui->sliderLabA, &ColorSlider::setValue);
    disconnect(ui->numberLabB,             &QDoubleSpinBox::valueChanged, ui->sliderLabB, &ColorSlider::setValue);
    disconnect(ui->numberAlpha,            &QDoubleSpinBox::valueChanged, ui->sliderAlpha, &ColorSlider::setValue);
    disconnect(ui->numberShade,            &QDoubleSpinBox::valueChanged, ui->sliderShade, &ColorSlider::setValue);

    // Color Harmony
    disconnect(ui->sliderHarmonyValue, &ColorSlider::colorChanged, this, &ColorPickerColor::changeColor);
    disconnect(ui->colorHarmonyWheel,  &ColorHarmonyWheel::colorChanged, this, &ColorPickerColor::changeColor);
    disconnect(ui->colorHarmonyWheel,  &ColorHarmonyWheel::harmonyChanged, this, &ColorPickerColor::changeColorButtons);
    disconnect(ui->buttonHarmony,      &QToolButton::triggered, ui->buttonHarmony, &QToolButton::setDefaultAction);
    disconnect(actionHarmonyAnalogous,             &QAction::triggered,this, &ColorPickerColor::changeHarmony );
    disconnect(actionHarmonyComplementary,         &QAction::triggered,this, &ColorPickerColor::changeHarmony );
    disconnect(actionHarmonyMonochromatic,         &QAction::triggered,this, &ColorPickerColor::changeHarmony );
    disconnect(actionHarmonySplitComplementary,    &QAction::triggered,this, &ColorPickerColor::changeHarmony );
    disconnect(actionHarmonySquare,                &QAction::triggered,this, &ColorPickerColor::changeHarmony );
    disconnect(actionHarmonyTetradic,              &QAction::triggered,this, &ColorPickerColor::changeHarmony );
    disconnect(actionHarmonyTriadic,               &QAction::triggered,this, &ColorPickerColor::changeHarmony );

    // Color Blindness
    disconnect(ui->buttonColorBlind,   &QToolButton::triggered, ui->buttonColorBlind, &QToolButton::setDefaultAction);
    disconnect(actionColorBlindNormal, &QAction::triggered,this, &ColorPickerColor::changeColorBlindness );
    disconnect(actionColorBlindRed,    &QAction::triggered,this, &ColorPickerColor::changeColorBlindness );
    disconnect(actionColorBlindGreen,  &QAction::triggered,this, &ColorPickerColor::changeColorBlindness );
    disconnect(actionColorBlindBlue,   &QAction::triggered,this, &ColorPickerColor::changeColorBlindness );
    disconnect(actionColorBlindFull,   &QAction::triggered,this, &ColorPickerColor::changeColorBlindness );

    // Color Buttons
    disconnect(ui->buttonColorMain,    &QToolButton::pressed, this, &ColorPickerColor::changeHarmonyColor );
    disconnect(ui->buttonColor1,       &QToolButton::pressed, this, &ColorPickerColor::changeHarmonyColor );
    disconnect(ui->buttonColor2,       &QToolButton::pressed, this, &ColorPickerColor::changeHarmonyColor );
    disconnect(ui->buttonColor3,       &QToolButton::pressed, this, &ColorPickerColor::changeHarmonyColor );
    disconnect(ui->buttonColor4,       &QToolButton::pressed, this, &ColorPickerColor::changeHarmonyColor );

    // Settings
    disconnect(actionColorBlind,       &QAction::toggled,this, &ColorPickerColor::switchColorBlind );
    disconnect(actionSliderScale,      &QAction::toggled,this, &ColorPickerColor::switchSliderScale );

    // Color Swatches
    disconnect(ui->swatches,           &ColorSwatches::colorChanged, this, &ColorPickerColor::setColorFromSwatch);

    // Sections
    disconnect(ui->sectionPicker,      &SectionContainer::collapsedState, this, &ColorPickerColor::changeSize);
    disconnect(ui->sectionSwatches,    &SectionContainer::collapsedState, this, &ColorPickerColor::changeSize);

    // Picker Button
    disconnect(buttonPickerToggle,     &QToolButton::triggered, buttonPickerToggle, &QToolButton::setDefaultAction);
    disconnect(actionPickerMap,        &QAction::triggered,this, &ColorPickerColor::changePickerMode );
    disconnect(actionPickerHarmony,    &QAction::triggered,this, &ColorPickerColor::changePickerMode );

    // Spot Button
    disconnect(ui->buttonSpotColor,    &QToolButton::toggled, this, &ColorPickerColor::setSpotFlag);

    // EyeDroper
    disconnect(ui->buttonEyeDropper,   &QToolButton::released, eyeDropper, &EyeDropperWidget::show);
    disconnect(eyeDropper,             &EyeDropperWidget::screenColor, this, &ColorPickerColor::changeColor);
}


/* ********************************************************************************* *
 *
 * Functions
 *
 * ********************************************************************************* */

void ColorPickerColor::updateColor(ScColor color)
{
    m_color = color;

    // Map
    if( ui->colorMap            != qobject_cast<ColorMap*>(sender()) )    ui->colorMap->setColor(color);
    if( ui->sliderUniversal     != qobject_cast<ColorSlider*>(sender()) ) ui->sliderUniversal->setColor(color);

    // CMYK
    if( ui->sliderCMYKCyan      != qobject_cast<ColorSlider*>(sender()) ) ui->sliderCMYKCyan->setColor(color);
    if( ui->sliderCMYKMagenta   != qobject_cast<ColorSlider*>(sender()) ) ui->sliderCMYKMagenta->setColor(color);
    if( ui->sliderCMYKYellow    != qobject_cast<ColorSlider*>(sender()) ) ui->sliderCMYKYellow->setColor(color);
    if( ui->sliderCMYKKey       != qobject_cast<ColorSlider*>(sender()) ) ui->sliderCMYKKey->setColor(color);

    // RGB
    if( ui->sliderRGBRed        != qobject_cast<ColorSlider*>(sender()) ) ui->sliderRGBRed->setColor(color);
    if( ui->sliderRGBGreen      != qobject_cast<ColorSlider*>(sender()) ) ui->sliderRGBGreen->setColor(color);
    if( ui->sliderRGBBlue       != qobject_cast<ColorSlider*>(sender()) ) ui->sliderRGBBlue->setColor(color);

    // HSV
    if( ui->sliderHSVHue        != qobject_cast<ColorSlider*>(sender()) ) ui->sliderHSVHue->setColor(color);
    if( ui->sliderHSVSaturation != qobject_cast<ColorSlider*>(sender()) ) ui->sliderHSVSaturation->setColor(color);
    if( ui->sliderHSVValue      != qobject_cast<ColorSlider*>(sender()) ) ui->sliderHSVValue->setColor(color);

    // Lab
    if( ui->sliderLabL          != qobject_cast<ColorSlider*>(sender()) ) ui->sliderLabL->setColor(color);
    if( ui->sliderLabA          != qobject_cast<ColorSlider*>(sender()) ) ui->sliderLabA->setColor(color);
    if( ui->sliderLabB          != qobject_cast<ColorSlider*>(sender()) ) ui->sliderLabB->setColor(color);

    // Alpha
    if( ui->sliderAlpha         != qobject_cast<ColorSlider*>(sender()) ) ui->sliderAlpha->setColor(color);

    // Shade
    if( ui->sliderShade         != qobject_cast<ColorSlider*>(sender()) ) ui->sliderShade->setColor(color);

    // Color Harmony Wheel
    if( ui->sliderHarmonyValue  != qobject_cast<ColorSlider*>(sender()) ) ui->sliderHarmonyValue->setColor(color);
    if( ui->colorHarmonyWheel   != qobject_cast<ColorHarmonyWheel*>(sender()) ) ui->colorHarmonyWheel->setColor(color);

    // Hex Input
    if( ui->textHex             != qobject_cast<QLineEdit*>(sender()) ) ui->textHex->setText(color.name());

    // Update Color Buttons
    updateColorButton(ui->buttonColorMain, color);
    updateColorButton(ui->buttonColor1, ui->colorHarmonyWheel->color(ColorHarmonyWheel::Variant1) );
    updateColorButton(ui->buttonColor2, ui->colorHarmonyWheel->color(ColorHarmonyWheel::Variant2) );
    updateColorButton(ui->buttonColor3, ui->colorHarmonyWheel->color(ColorHarmonyWheel::Variant3) );
    updateColorButton(ui->buttonColor4, ui->colorHarmonyWheel->color(ColorHarmonyWheel::Variant4) );

    // Update text label
    updateColorLabel();

}

void ColorPickerColor::updateColorButton(ColorButton *button, ScColor color)
{
    // Button Fill
    button->setColor(color);

    QColor col = color.toQColor();

    // Defect Color
    VisionDefectColor defect(col);
    defect.deficiency = m_defectMode;
    defect.convertDefect();
    QColor defectColor = defect.getColor();
    defectColor.setAlphaF(col.alphaF());

    // Button Dot
    int smallSide = button->foregroundDotSize().width();
    QBrush foreground( RenderUtils::renderSplitColor(QSize(smallSide, smallSide), defectColor) );
    button->setForeground(foreground);
}

void ColorPickerColor::updateColorLabel()
{
    QString colorLabel;

    switch(m_colorSpace){
    case ColorModel::HSV:
        colorLabel = QString("H:%1° S:%2% V:%3%")
                .arg(m_color.hue())
                .arg( qRound(m_color.saturationF() * 100) )
                .arg( qRound(m_color.valueF() * 100)
                      );
        break;
    case ColorModel::RGB:
        colorLabel = QString("R:%1 G:%2 B:%3")
                .arg( m_color.red() )
                .arg(m_color.green() )
                .arg(m_color.blue() );
        break;
    case ColorModel::CMYK:
        colorLabel = QString("C:%1% M:%2% Y:%3% K:%4%")
                .arg(QString::number(m_color.cyanF() * 100, 'f', 1) )
                .arg(QString::number(m_color.magentaF() * 100, 'f', 1) )
                .arg(QString::number(m_color.yellowF() * 100, 'f', 1) )
                .arg(QString::number(m_color.blackF() * 100, 'f', 1) );
        break;
    case ColorModel::Lab:
        colorLabel = QString("L:%1 a:%2 b:%3")
                .arg( QString::number(m_color.L(), 'f', 2) )
                .arg( QString::number(m_color.a(), 'f', 2) )
                .arg( QString::number(m_color.b(), 'f', 2) );
        break;
    }


}

void ColorPickerColor::setVisibleSwatches(bool isVisible)
{
    ui->sectionSwatches->setVisible(isVisible);
}

void ColorPickerColor::setVisiblePicker(bool isVisible)
{

    ui->sectionPicker->setVisible(isVisible);
}

void ColorPickerColor::setVisibleAlpha(bool isVisible)
{
    ui->labelAlpha->setVisible(isVisible);
    ui->sliderAlpha->setVisible(isVisible);
    ui->numberAlpha->setVisible(isVisible);
}

void ColorPickerColor::setVisibleShade(bool isVisible)
{
    ui->labelShade->setVisible(isVisible);
    ui->sliderShade->setVisible(isVisible);
    ui->numberShade->setVisible(isVisible);
}


/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

ScColor ColorPickerColor::color()
{
    ScColor col(m_color);

    switch(m_colorSpace){
    case ColorModel::HSV:
        return col.toHsv();
        break;
    case ColorModel::RGB:
        return col.toRgb();
        break;
    case ColorModel::CMYK:
        return col.toCmyk();
        break;
    case ColorModel::Lab:
        return col.toLab();
        break;
    }

    // should never reach
    return col;

}

void ColorPickerColor::setConfiguration(ColorPickerConfig config)
{
    m_configuration = config;

    disconnectSlots();

    switch(m_configuration){

    case ColorPickerConfig::StrokeMask:
    case ColorPickerConfig::FillMask:
        setVisiblePicker(true);
        setVisibleSwatches(true);
        setVisibleAlpha(true);
        setVisibleShade(false);
        break;

    case ColorPickerConfig::Fill:
    case ColorPickerConfig::Stroke:
    case ColorPickerConfig::Text:
    case ColorPickerConfig::Shadow:
        setVisiblePicker(true);
        setVisibleSwatches(true);
        setVisibleAlpha(true);
        setVisibleShade(true);
        break;

    default:
    case ColorPickerConfig::Default:
        setVisiblePicker(true);
        setVisibleSwatches(false);
        setVisibleAlpha(true);
        setVisibleShade(false);
        break;
    }

    changeUI();

    connectSlots();

}

ColorPickerConfig ColorPickerColor::configuration()
{
    return m_configuration;
}


/* ********************************************************************************* *
 *
 * Public Slots
 *
 * ********************************************************************************* */

void ColorPickerColor::setColor(ScColor color)
{
    updateColor(color);

    ColorModel colModel = color.getColorModel();
    int index = comboColorSpace->findData(QVariant::fromValue(colModel));

    if ( index != -1 ) {
        comboColorSpace->setCurrentIndex(index);
        m_colorSpace = colModel;
    }

    //ui->checkBox->setChecked(color.isSpotColor());
    ui->buttonSpotColor->setChecked(color.isSpotColor());

    changeUI();
}


/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */



void ColorPickerColor::switchColorBlind(bool enabled)
{
    bool state = (m_defectMode == VisionDefectColor::normalVision) ? false : enabled ;

    ui->buttonColorBlind->setVisible(enabled);
    ui->buttonColorMain->setHasDot(state);
    ui->buttonColor1->setHasDot(state);
    ui->buttonColor2->setHasDot(state);
    ui->buttonColor3->setHasDot(state);
    ui->buttonColor4->setHasDot(state);

}

void ColorPickerColor::switchSliderScale(bool enabled)
{
    QSlider::TickPosition hasTick = QSlider::TicksAbove;

    if(!enabled) hasTick = QSlider::NoTicks;

    // CMYK
    ui->sliderCMYKCyan->setTickPosition(hasTick);
    ui->sliderCMYKMagenta->setTickPosition(hasTick);
    ui->sliderCMYKYellow->setTickPosition(hasTick);
    ui->sliderCMYKKey->setTickPosition(hasTick);

    // RGB
    ui->sliderRGBRed->setTickPosition(hasTick);
    ui->sliderRGBGreen->setTickPosition(hasTick);
    ui->sliderRGBBlue->setTickPosition(hasTick);

    // HSV
    ui->sliderHSVHue->setTickPosition(hasTick);
    ui->sliderHSVSaturation->setTickPosition(hasTick);
    ui->sliderHSVValue->setTickPosition(hasTick);

    // Lab
    ui->sliderLabL->setTickPosition(hasTick);
    ui->sliderLabA->setTickPosition(hasTick);
    ui->sliderLabB->setTickPosition(hasTick);

    // Alpha
    ui->sliderAlpha->setTickPosition(hasTick);

    // Alpha
    ui->sliderShade->setTickPosition(hasTick);

}

void ColorPickerColor::setColorFromSwatch(ScColor color)
{
    setColor(color);
    emit colorChanged(this->color());
}

void ColorPickerColor::setSpotFlag(bool isSpot)
{
    m_color.setSpotColor(isSpot);
}



void ColorPickerColor::changeColor(ScColor color)
{
    // have to call everytime to update all ui elements
    updateColor(color);
    emit colorChanged(this->color());

}


void ColorPickerColor::changeColorBlindness()
{

    QAction *action = qobject_cast<QAction *>(sender());

    if(action != nullptr) m_defectMode = static_cast<VisionDefectColor::defectMode>(action->data().toInt());

    switch(m_defectMode){
    case VisionDefectColor::normalVision:
        ui->buttonColorMain->setHasDot(false);
        ui->buttonColor1->setHasDot(false);
        ui->buttonColor2->setHasDot(false);
        ui->buttonColor3->setHasDot(false);
        ui->buttonColor4->setHasDot(false);
        break;
    case VisionDefectColor::protanopeVision:
    case VisionDefectColor::deuteranopeVision:
    case VisionDefectColor::tritanopeVision:
    case VisionDefectColor::colorBlindnessVision:
        ui->buttonColorMain->setHasDot(true);
        ui->buttonColor1->setHasDot(true);
        ui->buttonColor2->setHasDot(true);
        ui->buttonColor3->setHasDot(true);
        ui->buttonColor4->setHasDot(true);
        break;
    }

    updateColor(m_color);

}

void ColorPickerColor::changeColorButtons(ColorHarmonyWheel::Harmony harmony)
{

    switch(harmony){
    case ColorHarmonyWheel::Complementary:
        ui->buttonColor1->setVisible(true);
        ui->buttonColor2->setVisible(false);
        ui->buttonColor3->setVisible(false);
        ui->buttonColor4->setVisible(false);
        break;
    case ColorHarmonyWheel::SplitComplementary:
    case ColorHarmonyWheel::Triadic:
        ui->buttonColor1->setVisible(true);
        ui->buttonColor2->setVisible(true);
        ui->buttonColor3->setVisible(false);
        ui->buttonColor4->setVisible(false);
        break;
    case ColorHarmonyWheel::Tetradic:
    case ColorHarmonyWheel::Square:
    case ColorHarmonyWheel::Monochromatic:
        ui->buttonColor1->setVisible(true);
        ui->buttonColor2->setVisible(true);
        ui->buttonColor3->setVisible(true);
        ui->buttonColor4->setVisible(false);
        break;
    case ColorHarmonyWheel::Analogous:
        ui->buttonColor1->setVisible(true);
        ui->buttonColor2->setVisible(true);
        ui->buttonColor3->setVisible(true);
        ui->buttonColor4->setVisible(true);
        break;
    default:
        ui->buttonColor1->setVisible(false);
        ui->buttonColor2->setVisible(false);
        ui->buttonColor3->setVisible(false);
        ui->buttonColor4->setVisible(false);
        break;

    }

}

void ColorPickerColor::changeColorSpace()
{

    m_colorSpace = static_cast<ColorModel>(comboColorSpace->currentData(Qt::UserRole).toInt());
    changeUI();
    emit colorChanged(this->color());
}

void ColorPickerColor::changeHarmony()
{
    QAction *action = qobject_cast<QAction *>(sender());

    if(action != nullptr) m_harmony = static_cast<ColorHarmonyWheel::Harmony>(action->data().toInt());

    ui->colorHarmonyWheel->setHarmony(m_harmony);

}

void ColorPickerColor::changeHarmonyColor()
{

    ColorButton *button = qobject_cast<ColorButton *>(sender());
    if(button != nullptr){
        changeColor(button->color());
    }
}

void ColorPickerColor::changeMapMode()
{
    QAction *action = qobject_cast<QAction *>(sender());

    if(action != nullptr) m_colorMapMode = static_cast<ColorMap::Mode>(action->data().toInt());

    switch(m_colorMapMode){
    case ColorMap::HSVHue:
        ui->colorMap->setMode(ColorMap::HSVHue);
        ui->sliderUniversal->setMode(ColorSlider::HSVHue);
        break;
    case ColorMap::HSVSaturation:
        ui->colorMap->setMode(ColorMap::HSVSaturation);
        ui->sliderUniversal->setMode(ColorSlider::HSVSaturation);
        break;
    case ColorMap::HSVValue:
        ui->colorMap->setMode(ColorMap::HSVValue);
        ui->sliderUniversal->setMode(ColorSlider::HSVValue);
        break;
    case ColorMap::RGBRed:
        ui->colorMap->setMode(ColorMap::RGBRed);
        ui->sliderUniversal->setMode(ColorSlider::RGBRed);
        break;
    case ColorMap::RGBGreen:
        ui->colorMap->setMode(ColorMap::RGBGreen);
        ui->sliderUniversal->setMode(ColorSlider::RGBGreen);
        break;
    case ColorMap::RGBBlue:
        ui->colorMap->setMode(ColorMap::RGBBlue);
        ui->sliderUniversal->setMode(ColorSlider::RGBBlue);
        break;
    case ColorMap::LabLightness:
        ui->colorMap->setMode(ColorMap::LabLightness);
        ui->sliderUniversal->setMode(ColorSlider::LabLightness);
        break;
    case ColorMap::LabA:
        ui->colorMap->setMode(ColorMap::LabA);
        ui->sliderUniversal->setMode(ColorSlider::LabA);
        break;
    case ColorMap::LabB:
        ui->colorMap->setMode(ColorMap::LabB);
        ui->sliderUniversal->setMode(ColorSlider::LabB);
        break;
    }
}

void ColorPickerColor::changeUI()
{
    // Reset harmony specific UI elements
    //  changeColorButtons(ColorHarmonyWheel::None);

    // Set slider & map based on color space
    switch(m_colorSpace){
    case ColorModel::HSV:
        ui->stackSlider->setCurrentIndex(0);
        m_colorMapMode = ColorMap::HSVHue;
        ui->buttonMapMode->setDefaultAction(actionMapHSVHue);
        break;
    case ColorModel::RGB:
        ui->stackSlider->setCurrentIndex(1);
        m_colorMapMode = ColorMap::HSVHue;
        ui->buttonMapMode->setDefaultAction(actionMapHSVHue);
        break;
    case ColorModel::CMYK:
        ui->stackSlider->setCurrentIndex(2);
        m_colorMapMode = ColorMap::HSVHue;
        ui->buttonMapMode->setDefaultAction(actionMapHSVHue);
        break;
    case ColorModel::Lab:
        ui->stackSlider->setCurrentIndex(3);
        m_colorMapMode = ColorMap::LabLightness;
        ui->buttonMapMode->setDefaultAction(actionMapLabL);
        break;
    }


    updateColorLabel();
    changeMapMode();
    changeHarmony();
    changePickerMode();


}

void ColorPickerColor::changeSize()
{
    adjustSize();
    emit sizeChanged();
}

void ColorPickerColor::changePickerMode()
{

    QAction *action = qobject_cast<QAction *>(sender());

    if(action != nullptr) m_pickerMode = static_cast<PickerMode>(action->data().toInt());

    switch(m_pickerMode){
    default:
    case PickerMode::Map:
        ui->stackPicker->setCurrentIndex(0);
        changeColorButtons(ColorHarmonyWheel::None);
        break;
    case PickerMode::Harmony:
        ui->stackPicker->setCurrentIndex(1);
        changeColorButtons(m_harmony);
        break;
    }

}



/* ********************************************************************************* *
 *
 * Events
 *
 * ********************************************************************************* */


void ColorPickerColor::mouseMoveEvent(QMouseEvent *e)
{
    //qDebug() << "global mouse pos" << e->globalPosition().toPoint();
}

void ColorPickerColor::mouseReleaseEvent(QMouseEvent *e)
{
    // qDebug() << "final global mouse pos" << e->globalPosition().toPoint();
}

