#include "component_spaceinput.h"
#include "iconmanager.h"
#include "ui_component_spaceinput.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

ComponentSpaceInput::ComponentSpaceInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentSpaceInput)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

ComponentSpaceInput::~ComponentSpaceInput()
{
    delete ui;
}

void ComponentSpaceInput::setup()
{

    IconManager &iconManager = IconManager::instance();

    ui->layoutBottom->setPixmap(iconManager.pixmap("space-bottom"));
    ui->layoutLeft->setPixmap(iconManager.pixmap("space-left"));
    ui->layoutRight->setPixmap(iconManager.pixmap("space-right"));
    ui->layoutTop->setPixmap(iconManager.pixmap("space-top"));
    ui->buttonLink->setIcon(iconManager.icon("link"));
    ui->buttonLink->setChecked(true);

//    adjustSize();
//    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//    setMinimumSize(sizeHint());


}

void ComponentSpaceInput::connectSlots()
{
    connect(ui->buttonLink, &QToolButton::toggled, this, &ComponentSpaceInput::linkInput);
}

/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

FormWidget *ComponentSpaceInput::layoutLeft()
{
    return ui->layoutLeft;
}

FormWidget *ComponentSpaceInput::layoutBottom()
{
    return ui->layoutBottom;
}

FormWidget *ComponentSpaceInput::layoutRight()
{
    return ui->layoutRight;
}

FormWidget *ComponentSpaceInput::layoutTop()
{
    return ui->layoutTop;
}

AdvancedSpinBox *ComponentSpaceInput::numberLeft()
{
    return ui->numberLeft;
}

AdvancedSpinBox *ComponentSpaceInput::numberBottom()
{
    return ui->numberBottom;
}

AdvancedSpinBox *ComponentSpaceInput::numberRight()
{
    return ui->numberRight;
}

AdvancedSpinBox *ComponentSpaceInput::numberTop()
{
    return ui->numberTop;
}

QToolButton *ComponentSpaceInput::buttonLink()
{
    return ui->buttonLink;
}

/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

void ComponentSpaceInput::linkInput(bool state)
{
    if(state){
        ui->buttonLink->setIcon(IconManager::instance().icon("link"));
    }else{
        ui->buttonLink->setIcon(IconManager::instance().icon("link-off"));
    }

    emit signalLinkInput(state);
}
