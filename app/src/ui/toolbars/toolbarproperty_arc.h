#ifndef TOOLBARPROPERTYARC_H
#define TOOLBARPROPERTYARC_H

#include "toolbarproperty.h"

#include <QDoubleSpinBox>

class ToolBarPropertyArc : public ToolBarProperty
{
public:
    ToolBarPropertyArc(QWidget * parent = nullptr);



private:
    QDoubleSpinBox * numberStartAngle;
    QDoubleSpinBox * numberEndAngle;


};

#endif // TOOLBARPROPERTYARC_H
