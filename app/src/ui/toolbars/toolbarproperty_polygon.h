#ifndef TOOLBARPROPERTYPOLYGON_H
#define TOOLBARPROPERTYPOLYGON_H

#include "toolbarproperty.h"
#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>

class ToolBarPropertyPolygon : public ToolBarProperty
{
public:
    ToolBarPropertyPolygon(QWidget * parent = nullptr);

private:

    QSpinBox * numberCorners;
    QSpinBox * numberRotation;
    QSpinBox * numberFactor;
    QSpinBox * numberInnerRotation;
    QSpinBox * numberInnerCurvation;
    QSpinBox * numberOuterCurvation;
    QCheckBox * checkboxApplyFactor;
    QLabel * labelCorners;
    QLabel * labelRotation;
    QLabel * labelFactor;
    QLabel * labelInnerRotation;
    QLabel * labelInnerCurvation;
    QLabel * labelOuterCurvation;

private slots:
    void enableControls(bool enabled);

};

#endif // TOOLBARPROPERTYPOLYGON_H
