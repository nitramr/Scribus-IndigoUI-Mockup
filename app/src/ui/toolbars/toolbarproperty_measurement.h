#ifndef TOOLBARPROPERTYMEASUREMENT_H
#define TOOLBARPROPERTYMEASUREMENT_H

#include "toolbarproperty.h"
#include "_combobox/unit_combobox.h"
#include <QWidget>
#include <QDoubleSpinBox>

class ToolBarPropertyMeasurement : public ToolBarProperty
{
public:
    ToolBarPropertyMeasurement(QWidget * parent = nullptr);

private:

    QDoubleSpinBox * numberX1;
    QDoubleSpinBox * numberY1;
    QDoubleSpinBox * numberX2;
    QDoubleSpinBox * numberY2;
    QDoubleSpinBox * numberLength;
    QDoubleSpinBox * numberDX;
    QDoubleSpinBox * numberDY;
    QDoubleSpinBox * numberAngle;
    UnitComboBox * comboboxUnit;

    QString m_unit;

private slots:
    void changeUnit(int index);

};

#endif // TOOLBARPROPERTYMEASUREMENT_H
