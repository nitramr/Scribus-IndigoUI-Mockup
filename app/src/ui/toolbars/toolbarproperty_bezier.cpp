#include "toolbarproperty_bezier.h"
#include "form_widget/form_widget.h"
#include <QHBoxLayout>
#include "qspinbox.h"
#include "icon_manager.h"

ToolBarPropertyBezier::ToolBarPropertyBezier(QWidget *parent) : ToolBarProperty(parent)
{

    QFont fontLabel = this->font();
    fontLabel.setPointSize(8);

    IconManager &iconManager = IconManager::instance();

    setIcon( iconManager.pixmap("tool-edit") );

    // Controls
    buttonSymetricControl = new QToolButton();
    buttonSymetricControl->setIcon( iconManager.icon("bezier-control-symetric") );
    buttonAsymetricControl = new QToolButton();
    buttonAsymetricControl->setIcon( iconManager.icon("bezier-control-asymetric") );
    buttonResetControl = new QToolButton();
    buttonResetControl->setIcon( iconManager.icon("bezier-control-reset") );
    buttonResetControls = new QToolButton();
    buttonResetControls->setIcon( iconManager.icon("bezier-controls-reset") );

    // Nodes
    buttonAddNode = new QToolButton();
    buttonAddNode->setIcon( iconManager.icon("bezier-add-node") );
    buttonRemoveNode = new QToolButton();
    buttonRemoveNode->setIcon( iconManager.icon("bezier-remove-node") );

    // Path
    buttonOpenPath = new QToolButton();
    buttonOpenPath->setIcon( iconManager.icon("bezier-path-open") );
    buttonClosePath = new QToolButton();
    buttonClosePath->setIcon( iconManager.icon("bezier-path-close") );

    // Transformation
    buttonMirrorPathHorizontal = new QToolButton();
    buttonMirrorPathHorizontal->setIcon( iconManager.icon("bezier-path-flip-horizontal") );
    buttonMirrorPathVertical = new QToolButton();
    buttonMirrorPathVertical->setIcon( iconManager.icon("bezier-path-flip-vertical") );

    buttonShearPathRight = new QToolButton();
    buttonShearPathRight->setIcon( iconManager.icon("bezier-path-shear-right") );
    buttonShearPathLeft = new QToolButton();
    buttonShearPathLeft->setIcon( iconManager.icon("bezier-path-shear-left") );
    buttonShearPathUp = new QToolButton();
    buttonShearPathUp->setIcon( iconManager.icon("bezier-path-shear-up") );
    buttonShearPathDown = new QToolButton();
    buttonShearPathDown->setIcon( iconManager.icon("bezier-path-shear-down") );

    buttonRotatePathLeft = new QToolButton();
    buttonRotatePathLeft->setIcon( iconManager.icon("bezier-path-rotate-left") );
    buttonRotatePathRight = new QToolButton();
    buttonRotatePathRight->setIcon( iconManager.icon("bezier-path-rotate-right") );
    numberRotatePath = new AdvancedSpinBox();
    numberRotatePath->setSuffix("°");
    numberRotatePath->setDecimals(0);

    buttonExtentPath = new QToolButton();
    buttonExtentPath->setIcon( iconManager.icon("bezier-path-expand") );
    buttonShrinkPath = new QToolButton();
    buttonShrinkPath->setIcon( iconManager.icon("bezier-path-shrink") );
    numberScalePath = new AdvancedSpinBox();

    numberXPos = new AdvancedSpinBox();
    numberYPos = new AdvancedSpinBox();

    // Extras
    checkboxEditContour = new QCheckBox();
    checkboxEditContour->setText(tr("Edit Contour"));
    checkboxHideNodes = new QCheckBox();
    checkboxHideNodes->setText(tr("Hide Nodes"));


    this->addWidget(buttonSymetricControl);
    this->addWidget(buttonAsymetricControl);
    this->addWidget(buttonResetControl);
    this->addWidget(buttonResetControls);
    this->addSeparator();
    this->addWidget(buttonAddNode);
    this->addWidget(buttonRemoveNode);
    this->addSeparator();
    this->addWidget(buttonOpenPath);
    this->addWidget(buttonClosePath);
    this->addSeparator();
    this->addWidget(buttonMirrorPathHorizontal);
    this->addWidget(buttonMirrorPathVertical);
    this->addSeparator();
    this->addWidget(buttonShearPathRight);
    this->addWidget(buttonShearPathLeft);
    this->addWidget(buttonShearPathUp);
    this->addWidget(buttonShearPathDown);
    this->addSeparator();
    this->addWidget(numberRotatePath);
    this->addWidget(buttonRotatePathLeft);
    this->addWidget(buttonRotatePathRight);
    this->addSeparator();
    this->addWidget(numberScalePath);
    this->addWidget(buttonExtentPath);
    this->addWidget(buttonShrinkPath);
    this->addSeparator();
    this->addFormWidget("x", tr("X:"), QList<QWidget*>() << numberXPos );
    this->addFormWidget("y", tr("Y:"), QList<QWidget*>() << numberYPos );
    this->addSeparator();
    this->addWidget(checkboxEditContour);
    this->addSpacing(4);
    this->addWidget(checkboxHideNodes);

}
