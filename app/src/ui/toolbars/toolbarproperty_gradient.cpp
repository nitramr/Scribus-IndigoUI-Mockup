#include "toolbarproperty_gradient.h"
#include "icon_manager.h"


ToolBarPropertyGradient::ToolBarPropertyGradient(QWidget *parent) : ToolBarProperty(parent)
{

    IconManager &iconManager = IconManager::instance();

    setIcon( iconManager.pixmap("tool-gradient") );


    // Dummy toggle to switch the different gradient types
    comboType = new QComboBox();
    comboType->addItem(tr("Linear"), QVariant::fromValue(GradientType::Linear));
    comboType->addItem(tr("Radial"), QVariant::fromValue(GradientType::Radial));
    comboType->addItem(tr("Conical"), QVariant::fromValue(GradientType::Conical));
    comboType->addItem(tr("Diamond"), QVariant::fromValue(GradientType::Diamond));
    comboType->addItem(tr("4 Colors"), QVariant::fromValue(GradientType::FourColors));
    comboType->addItem(tr("Mesh"), QVariant::fromValue(GradientType::Mesh));
    comboType->addItem(tr("Patch Mesh"), QVariant::fromValue(GradientType::PatchMesh));
    comboType->setCurrentIndex(0);


    numberStartX = new AdvancedSpinBox();
    numberStartY = new AdvancedSpinBox();
    numberEndX = new AdvancedSpinBox();
    numberEndY = new AdvancedSpinBox();
    numberFocalX = new AdvancedSpinBox();
    numberFocalY = new AdvancedSpinBox();

    numberSkew = new AdvancedSpinBox();
    numberSkew->setSuffix("°");
    numberSkew->setDecimals(2);

    numberScale = new AdvancedSpinBox();
    numberScale->setSuffix("%");
    numberScale->setDecimals(2);

    numberPoint1X = new AdvancedSpinBox();
    numberPoint1Y = new AdvancedSpinBox();
    numberPoint2X = new AdvancedSpinBox();
    numberPoint2Y = new AdvancedSpinBox();
    numberPoint3X = new AdvancedSpinBox();
    numberPoint3Y = new AdvancedSpinBox();
    numberPoint4X = new AdvancedSpinBox();
    numberPoint4Y = new AdvancedSpinBox();
    numberPoint5X = new AdvancedSpinBox();
    numberPoint5Y = new AdvancedSpinBox();

    buttonAddPatch = new QToolButton();
    buttonAddPatch->setIcon( iconManager.icon("patchmesh-add") );
    buttonAddPatch->setIconSize(this->iconSize());
    buttonAddPatch->setAutoRaise(true);

    buttonRemovePatch = new QToolButton();
    buttonRemovePatch->setIcon( iconManager.icon("patchmesh-remove") );
    buttonRemovePatch->setIconSize(this->iconSize());
    buttonRemovePatch->setAutoRaise(true);

    buttonResetControl = new QToolButton();
    buttonResetControl->setIcon( iconManager.icon("bezier-control-reset") );
    buttonResetControl->setIconSize(this->iconSize());
    buttonResetControl->setAutoRaise(true);

    buttonResetControls = new QToolButton();
    buttonResetControls->setIcon( iconManager.icon("bezier-controls-reset") );
    buttonResetControls->setIconSize(this->iconSize());
    buttonResetControls->setAutoRaise(true);

    buttonResetMesh = new QToolButton();
    buttonResetMesh->setIcon( iconManager.icon("mesh-reset") );
    buttonResetMesh->setIconSize(this->iconSize());
    buttonResetMesh->setAutoRaise(true);

    buttonMeshToShape = new QToolButton();
    buttonMeshToShape->setIcon( iconManager.icon("mesh-to-shape") );
    buttonMeshToShape->setIconSize(this->iconSize());
    buttonMeshToShape->setAutoRaise(true);

    checkboxSnapMesh = new QCheckBox();
    checkboxSnapMesh->setText( tr("Snap to other Mesh Points") );

    numberRow = new QSpinBox();
    numberColumn = new QSpinBox();


    // Add Widgets
    this->addWidget(comboType);
    connect(comboType, &QComboBox::currentIndexChanged, this, &ToolBarPropertyGradient::toggleType);

    this->addFormWidget("start", tr("Start:"), QList<QWidget*>() << numberStartX << numberStartY );
    this->addFormWidget("end", tr("End:"), QList<QWidget*>() << numberEndX << numberEndY );
    this->addFormWidget("focal", tr("Focal:"), QList<QWidget*>() << numberFocalX << numberFocalY );
    this->addFormWidget("skew", tr("Skew:"), QList<QWidget*>() << numberSkew );
    this->addFormWidget("scale", tr("Scale:"), QList<QWidget*>() << numberScale );

    this->addFormWidget("point1", tr("Point 1:"), QList<QWidget*>() << numberPoint1X << numberPoint1Y );
    this->addFormWidget("point2", tr("Point 2:"), QList<QWidget*>() << numberPoint2X << numberPoint2Y );
    this->addFormWidget("point3", tr("Point 3:"), QList<QWidget*>() << numberPoint3X << numberPoint3Y );
    this->addFormWidget("point4", tr("Point 4:"), QList<QWidget*>() << numberPoint4X << numberPoint4Y );
    this->addFormWidget("point5", tr("Point 5:"), QList<QWidget*>() << numberPoint5X << numberPoint5Y );

    this->addFormWidget("controls", "", QList<QWidget*>() << buttonResetControl << buttonResetControls);
    this->addFormWidget("patch", "", QList<QWidget*>() << buttonAddPatch << buttonRemovePatch << checkboxSnapMesh );
    this->addFormWidget("rows", tr("Rows:"), QList<QWidget*>() << numberRow  );
    this->addFormWidget("colum", tr("Columns:"), QList<QWidget*>() << numberColumn  );
    this->addFormWidget("mesh", "", QList<QWidget*>() << buttonResetMesh << buttonMeshToShape );

    toggleType();

}

void ToolBarPropertyGradient::setGradientType(GradientType type)
{
    m_gradientType = type;

    setFormWidgetVisibility("start", false);
    setFormWidgetVisibility("end", false);
    setFormWidgetVisibility("focal", false);
    setFormWidgetVisibility("skew", false);
    setFormWidgetVisibility("scale", false);
    setFormWidgetVisibility("point1", false);
    setFormWidgetVisibility("point2", false);
    setFormWidgetVisibility("point3", false);
    setFormWidgetVisibility("point4", false);
    setFormWidgetVisibility("point5", false);
    setFormWidgetVisibility("controls", false);
    setFormWidgetVisibility("rows", false);
    setFormWidgetVisibility("colum", false);
    setFormWidgetVisibility("mesh", false);
    setFormWidgetVisibility("patch", false);

    switch(m_gradientType){
    case GradientType::Linear:
        setFormWidgetVisibility("start", true);
        setFormWidgetVisibility("end", true);
        setFormWidgetVisibility("skew", true);
        break;
    case GradientType::Radial:
        setFormWidgetVisibility("start", true);
        setFormWidgetVisibility("end", true);
        setFormWidgetVisibility("focal", true);
        setFormWidgetVisibility("skew", true);
        setFormWidgetVisibility("scale", true);
        break;
    case GradientType::Conical:
        setFormWidgetVisibility("start", true);
        setFormWidgetVisibility("end", true);
        setFormWidgetVisibility("focal", true);
        setFormWidgetVisibility("scale", true);
        break;
    case GradientType::Diamond:
        setFormWidgetVisibility("point1", true);
        setFormWidgetVisibility("point2", true);
        setFormWidgetVisibility("point3", true);
        setFormWidgetVisibility("point4", true);
        setFormWidgetVisibility("point5", true);
        break;
    case GradientType::FourColors:
        setFormWidgetVisibility("point1", true);
        setFormWidgetVisibility("point2", true);
        setFormWidgetVisibility("point3", true);
        setFormWidgetVisibility("point4", true);
        break;
    case GradientType::Mesh:
        setFormWidgetVisibility("controls", true);
        setFormWidgetVisibility("rows", true);
        setFormWidgetVisibility("colum", true);
        setFormWidgetVisibility("mesh", true);
        break;
    case GradientType::PatchMesh:
        setFormWidgetVisibility("controls", true);
        setFormWidgetVisibility("patch", true);
        break;
    }
}

void ToolBarPropertyGradient::toggleType()
{
     GradientType type = static_cast<GradientType>(comboType->currentData().toInt());

     setGradientType(type);
}

