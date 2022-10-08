#ifndef TOOLBARPROPERTYGRADIENT_H
#define TOOLBARPROPERTYGRADIENT_H

#include "advanced_spinbox/advanced_spinbox.h"
#include "enums.h"
#include "toolbarproperty.h"
#include <QWidget>
#include <QToolButton>
#include <QCheckBox>
#include <QComboBox>

class ToolBarPropertyGradient : public ToolBarProperty
{
public:
    ToolBarPropertyGradient(QWidget * parent = nullptr);

private:

    GradientType m_gradientType;

    // Widgets
    QComboBox * comboType;
    AdvancedSpinBox * numberStartX;
    AdvancedSpinBox * numberStartY;
    AdvancedSpinBox * numberEndX;
    AdvancedSpinBox * numberEndY;
    AdvancedSpinBox * numberFocalX;
    AdvancedSpinBox * numberFocalY;
    AdvancedSpinBox * numberSkew;
    AdvancedSpinBox * numberScale;
    AdvancedSpinBox * numberPoint1X;
    AdvancedSpinBox * numberPoint1Y;
    AdvancedSpinBox * numberPoint2X;
    AdvancedSpinBox * numberPoint2Y;
    AdvancedSpinBox * numberPoint3X;
    AdvancedSpinBox * numberPoint3Y;
    AdvancedSpinBox * numberPoint4X;
    AdvancedSpinBox * numberPoint4Y;
    AdvancedSpinBox * numberPoint5X;
    AdvancedSpinBox * numberPoint5Y;
    QToolButton * buttonAddPatch;
    QToolButton * buttonRemovePatch;
    QToolButton * buttonResetControl;
    QToolButton * buttonResetControls;
    QToolButton * buttonResetMesh;
    QToolButton * buttonMeshToShape;
    QCheckBox * checkboxSnapMesh;
    QSpinBox * numberRow;
    QSpinBox * numberColumn;


    void setGradientType(GradientType type);

private slots:
    void toggleType();


};

#endif // TOOLBARPROPERTYGRADIENT_H
