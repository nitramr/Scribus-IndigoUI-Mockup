#ifndef TOOLBARPROPERTYCALLIGRAPHY_H
#define TOOLBARPROPERTYCALLIGRAPHY_H

#include "toolbarproperty.h"
#include <QWidget>
#include <QDoubleSpinBox>

class ToolBarPropertyCalligraphy : public ToolBarProperty
{
public:
    ToolBarPropertyCalligraphy(QWidget * parent = nullptr);

private:

    QLabel * labelAngle;
    QDoubleSpinBox * numberAngle;
    QLabel * labelWidth;
    QDoubleSpinBox * numberWidth;

};

#endif // TOOLBARPROPERTYCALLIGRAPHY_H
