#ifndef COMPONENT_PAGELAYOUT_H
#define COMPONENT_PAGELAYOUT_H

#include "advancedspinbox.h"
#include <QComboBox>
#include <QCheckBox>
#include <QButtonGroup>
#include <QWidget>

namespace Ui {
class ComponentPageLayout;
}

class ComponentPageLayout : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentPageLayout(QWidget *parent = nullptr);
    ~ComponentPageLayout();

    QComboBox * comboPageSize();
    QComboBox * comboUnits();
    AdvancedSpinBox * numberPageWidth();
    AdvancedSpinBox * numberPageHeight();
    QCheckBox * checkBoxMoveObjects();

    void setUnitVisibility(bool isVisible);
    bool unitVisibility();

    void setMoveObjectsVisibility(bool isVisible);
    bool moveObjectsVisibility();

private:
    Ui::ComponentPageLayout *ui;

    QButtonGroup * orientationButtons;

    void setup();
};

#endif // COMPONENT_PAGELAYOUT_H
