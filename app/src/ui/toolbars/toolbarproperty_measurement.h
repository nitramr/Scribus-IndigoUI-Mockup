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

    QLabel * labelX1;
    QDoubleSpinBox * numberX1;
    QLabel * labelY1;
    QDoubleSpinBox * numberY1;
    QLabel * labelX2;
    QDoubleSpinBox * numberX2;
    QLabel * labelY2;
    QDoubleSpinBox * numberY2;
    QLabel * labelLength;
    QDoubleSpinBox * numberLength;
    QLabel * labelDX;
    QDoubleSpinBox * numberDX;
    QLabel * labelDY;
    QDoubleSpinBox * numberDY;
    QLabel * labelAngle;
    QDoubleSpinBox * numberAngle;
    QLabel * labelUnit;
    UnitComboBox * comboboxUnit;

    QString m_unit;

private slots:
    void changeUnit(int index);

};

#endif // TOOLBARPROPERTYMEASUREMENT_H
