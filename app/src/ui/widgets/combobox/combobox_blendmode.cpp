#include "combobox_blendmode.h"
#include "enums.h"

ComboBoxBlendMode::ComboBoxBlendMode(QWidget *parent) : QComboBox(parent)
{
    this->addItem("Normal", QVariant::fromValue(ColorBlendMode::Normal));
    this->addItem("Darken", QVariant::fromValue(ColorBlendMode::Darken));
    this->addItem("Lighten", QVariant::fromValue(ColorBlendMode::Lighten));
    this->addItem("Multiply", QVariant::fromValue(ColorBlendMode::Multiply));
    this->addItem("Screen", QVariant::fromValue(ColorBlendMode::Screen));
    this->addItem("Overlay", QVariant::fromValue(ColorBlendMode::Overlay));
    this->addItem("Hard Light", QVariant::fromValue(ColorBlendMode::HardLight));
    this->addItem("Soft Light", QVariant::fromValue(ColorBlendMode::SoftLight));
    this->addItem("Difference", QVariant::fromValue(ColorBlendMode::Difference));
    this->addItem("Exclusion", QVariant::fromValue(ColorBlendMode::Exclusion));
    this->addItem("Color Dodge", QVariant::fromValue(ColorBlendMode::ColorDodge));
    this->addItem("Color Burn", QVariant::fromValue(ColorBlendMode::ColorBurn));
    this->addItem("Hue", QVariant::fromValue(ColorBlendMode::Hue));
    this->addItem("Saturation", QVariant::fromValue(ColorBlendMode::Saturation));
    this->addItem("Color", QVariant::fromValue(ColorBlendMode::Color));
    this->addItem("Luminosity", QVariant::fromValue(ColorBlendMode::Luminosity));

}
