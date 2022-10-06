#include "toolbarproperty_measurement.h"
#include "enums.h"
#include "icon_manager.h"

ToolBarPropertyMeasurement::ToolBarPropertyMeasurement(QWidget *parent) : ToolBarProperty(parent)
{

    IconManager &iconManager = IconManager::instance();

    setIcon( iconManager.pixmap("tool-measure") );


    m_unit = QString(tr("mm"));

    labelX1 = new QLabel(tr("X1:"));
    numberX1 = new QDoubleSpinBox();
    numberX1->setSuffix(m_unit);
    numberX1->setReadOnly(true);
    numberX1->setButtonSymbols(QAbstractSpinBox::NoButtons);

    labelY1 = new QLabel(tr("Y1:"));
    numberY1 = new QDoubleSpinBox();
    numberY1->setSuffix(m_unit);
    numberY1->setReadOnly(true);
    numberY1->setButtonSymbols(QAbstractSpinBox::NoButtons);

    labelX2 = new QLabel(tr("X2:"));
    numberX2 = new QDoubleSpinBox();
    numberX2->setSuffix(m_unit);
    numberX2->setReadOnly(true);
    numberX2->setButtonSymbols(QAbstractSpinBox::NoButtons);

    labelY2 = new QLabel(tr("Y2:"));
    numberY2 = new QDoubleSpinBox();
    numberY2->setSuffix(m_unit);
    numberY2->setReadOnly(true);
    numberY2->setButtonSymbols(QAbstractSpinBox::NoButtons);

    labelLength = new QLabel(tr("Length:"));
    numberLength = new QDoubleSpinBox();
    numberLength->setSuffix(m_unit);
    numberLength->setReadOnly(true);
    numberLength->setButtonSymbols(QAbstractSpinBox::NoButtons);

    labelDX = new QLabel(tr("DX:"));
    numberDX = new QDoubleSpinBox();
    numberDX->setSuffix(m_unit);
    numberDX->setReadOnly(true);
    numberDX->setButtonSymbols(QAbstractSpinBox::NoButtons);

    labelDY = new QLabel(tr("DY:"));
    numberDY = new QDoubleSpinBox();
    numberDY->setSuffix(m_unit);
    numberDY->setReadOnly(true);
    numberDY->setButtonSymbols(QAbstractSpinBox::NoButtons);

    labelAngle = new QLabel(tr("Angle:"));
    numberAngle = new QDoubleSpinBox();
    numberAngle->setSuffix(tr("°"));
    numberAngle->setReadOnly(true);
    numberAngle->setButtonSymbols(QAbstractSpinBox::NoButtons);

    labelUnit = new QLabel(tr("Unit:"));
    comboboxUnit = new UnitComboBox();

    connect(comboboxUnit, &UnitComboBox::currentIndexChanged, this, &ToolBarPropertyMeasurement::changeUnit);

    this->addWidget(labelUnit);
    this->addWidget(comboboxUnit);
    this->addSpacing(4);
    this->addWidget(labelX1);
    this->addWidget(numberX1);
    this->addSpacing(4);
    this->addWidget(labelY1);
    this->addWidget(numberY1);
    this->addSpacing(4);
    this->addWidget(labelX2);
    this->addWidget(numberX2);
    this->addSpacing(4);
    this->addWidget(labelY2);
    this->addWidget(numberY2);
    this->addSpacing(4);
    this->addWidget(labelLength);
    this->addWidget(numberLength);
    this->addSpacing(4);
    this->addWidget(labelDX);
    this->addWidget(numberDX);
    this->addSpacing(4);
    this->addWidget(labelDY);
    this->addWidget(numberDY);
    this->addSpacing(4);
    this->addWidget(labelAngle);
    this->addWidget(numberAngle);


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
