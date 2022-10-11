#ifndef TOOLBARPROPERTYSPIRAL_H
#define TOOLBARPROPERTYSPIRAL_H

#include "toolbarproperty.h"
#include <QWidget>
#include <QDoubleSpinBox>

class ToolBarPropertySpiral :  public ToolBarProperty
{
public:
    ToolBarPropertySpiral(QWidget * parent = nullptr);

private:
    QDoubleSpinBox * numberStartAngle;
    QDoubleSpinBox * numberEndAngle;
    QSpinBox * numberFactor;

};

#endif // TOOLBARPROPERTYSPIRAL_H
