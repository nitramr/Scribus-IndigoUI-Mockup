#include "unit_combobox.h"
#include "enums.h"

UnitComboBox::UnitComboBox(QWidget *parent)
    : QComboBox{parent}
{ 

    this->addItem(tr("Points (pt)"), QVariant::fromValue(PageUnits::Points));
    this->addItem(tr("Millimeters (mm)"), QVariant::fromValue(PageUnits::Millimeters));
    this->addItem(tr("Inches (in)"), QVariant::fromValue(PageUnits::Inches));
    this->addItem(tr("Picas (p)"), QVariant::fromValue(PageUnits::Picas));
    this->addItem(tr("Centimeters (cm)"), QVariant::fromValue(PageUnits::Centimeters));
    this->addItem(tr("Cicero (c)"), QVariant::fromValue(PageUnits::Cicero));
    this->setCurrentIndex(1);
}
