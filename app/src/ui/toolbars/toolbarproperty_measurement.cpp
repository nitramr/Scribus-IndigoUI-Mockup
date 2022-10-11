#include "toolbarproperty_measurement.h"
#include "enums.h"
#include "icon_manager.h"

ToolBarPropertyMeasurement::ToolBarPropertyMeasurement(QWidget *parent) : ToolBarProperty(parent)
{

    IconManager &iconManager = IconManager::instance();

    setIcon( iconManager.pixmap("tool-measure") );


    m_unit = QString(tr("mm"));

    numberX1 = new QDoubleSpinBox();
    numberX1->setSuffix(m_unit);
    numberX1->setReadOnly(true);
    numberX1->setButtonSymbols(QAbstractSpinBox::NoButtons);

    numberY1 = new QDoubleSpinBox();
    numberY1->setSuffix(m_unit);
    numberY1->setReadOnly(true);
    numberY1->setButtonSymbols(QAbstractSpinBox::NoButtons);

    numberX2 = new QDoubleSpinBox();
    numberX2->setSuffix(m_unit);
    numberX2->setReadOnly(true);
    numberX2->setButtonSymbols(QAbstractSpinBox::NoButtons);

    numberY2 = new QDoubleSpinBox();
    numberY2->setSuffix(m_unit);
    numberY2->setReadOnly(true);
    numberY2->setButtonSymbols(QAbstractSpinBox::NoButtons);

    numberLength = new QDoubleSpinBox();
    numberLength->setSuffix(m_unit);
    numberLength->setReadOnly(true);
    numberLength->setButtonSymbols(QAbstractSpinBox::NoButtons);

    numberDX = new QDoubleSpinBox();
    numberDX->setSuffix(m_unit);
    numberDX->setReadOnly(true);
    numberDX->setButtonSymbols(QAbstractSpinBox::NoButtons);

    numberDY = new QDoubleSpinBox();
    numberDY->setSuffix(m_unit);
    numberDY->setReadOnly(true);
    numberDY->setButtonSymbols(QAbstractSpinBox::NoButtons);

    numberAngle = new QDoubleSpinBox();
    numberAngle->setSuffix(tr("°"));
    numberAngle->setReadOnly(true);
    numberAngle->setButtonSymbols(QAbstractSpinBox::NoButtons);

    comboboxUnit = new UnitComboBox();

    connect(comboboxUnit, &UnitComboBox::currentIndexChanged, this, &ToolBarPropertyMeasurement::changeUnit);


    this->addFormWidget("unit", tr("Unit:"), QList<QWidget*>() << comboboxUnit );
    this->addFormWidget("x1", tr("X1:"), QList<QWidget*>() << numberX1 );
    this->addFormWidget("y1", tr("Y1:"), QList<QWidget*>() << numberY1 );
    this->addFormWidget("x2", tr("X2:"), QList<QWidget*>() << numberX2 );
    this->addFormWidget("y2", tr("Y2:"), QList<QWidget*>() << numberY2 );
    this->addFormWidget("length", tr("Length:"), QList<QWidget*>() << numberLength );
    this->addFormWidget("dx", tr("DX:"), QList<QWidget*>() << numberDX );
    this->addFormWidget("dy", tr("DY:"), QList<QWidget*>() << numberDY );
    this->addFormWidget("angle", tr("Angle:"), QList<QWidget*>() << numberAngle );


}

void ToolBarPropertyMeasurement::changeUnit(int index)
{

    Q_UNUSED(index);

    PageUnits pageUnit = static_cast<PageUnits>(comboboxUnit->currentData(Qt::UserRole).toInt());

    switch(pageUnit){
    case PageUnits::Centimeters:
        m_unit = tr("cm");
        break;
    case PageUnits::Cicero:
        m_unit = tr("c");
        break;
    case PageUnits::Inches:
        m_unit = tr("in");
        break;
    case PageUnits::Millimeters:
        m_unit = tr("mm");
        break;
    case PageUnits::Picas:
        m_unit = tr("p");
        break;
    case PageUnits::Points:
        m_unit = tr("pt");
        break;
    }

    numberX1->setSuffix(m_unit);
    numberY1->setSuffix(m_unit);
    numberX2->setSuffix(m_unit);
    numberY2->setSuffix(m_unit);
    numberLength->setSuffix(m_unit);
    numberDX->setSuffix(m_unit);
    numberDY->setSuffix(m_unit);

}
