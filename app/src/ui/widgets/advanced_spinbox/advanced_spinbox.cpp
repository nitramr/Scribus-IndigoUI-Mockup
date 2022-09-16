#include "advanced_spinbox.h"

AdvancedSpinBox::AdvancedSpinBox(QWidget *parent) : QDoubleSpinBox(parent)
{
    this->setDecimals(3);
    this->setSuffix("mm");
}


AdvancedSpinBox::~AdvancedSpinBox()
{
}

