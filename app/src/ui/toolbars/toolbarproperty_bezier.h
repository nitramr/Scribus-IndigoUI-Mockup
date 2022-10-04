#ifndef TOOLBARPROPERTYBEZIER_H
#define TOOLBARPROPERTYBEZIER_H

#include "advanced_spinbox/advanced_spinbox.h"
#include "toolbarproperty.h"
#include <QToolButton>
#include <QCheckBox>

class ToolBarPropertyBezier : public ToolBarProperty
{
public:
    ToolBarPropertyBezier(QWidget *parent = nullptr);

private:
    // Controls
    QToolButton * buttonSymetricControl;
    QToolButton * buttonAsymetricControl;
    QToolButton * buttonResetControl;
    QToolButton * buttonResetControls;

    // Nodes
    QToolButton * buttonAddNode;
    QToolButton * buttonRemoveNode;

    // Path
    QToolButton * buttonOpenPath;
    QToolButton * buttonClosePath;

    // Transformation
    QToolButton * buttonMirrorPathHorizontal;
    QToolButton * buttonMirrorPathVertical;

    QToolButton * buttonShearPathRight;
    QToolButton * buttonShearPathLeft;
    QToolButton * buttonShearPathUp;
    QToolButton * buttonShearPathDown;

    QToolButton * buttonRotatePathRight;
    QToolButton * buttonRotatePathLeft;
    AdvancedSpinBox * numberRotatePath;

    QToolButton * buttonExtentPath;
    QToolButton * buttonShrinkPath;
    AdvancedSpinBox * numberScalePath;

    AdvancedSpinBox * numberXPos;
    AdvancedSpinBox * numberYPos;

    // Extras
    QCheckBox * checkboxEditContour;
    QCheckBox * checkboxHideNodes;



};

#endif // TOOLBARPROPERTYBEZIER_H
