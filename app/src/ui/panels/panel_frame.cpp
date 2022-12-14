#include "panel_frame.h"
//#include "flowlayout.h"
#include "ui_panel_frame.h"

#include <QComboBox>

#include "icon_manager.h"
#include "popup_menu/popup_menu.h"
#include "section_container/section_container.h"

PanelFrame::PanelFrame(QWidget *parent) :
    Panel(parent),
    ui(new Ui::PanelFrame)
{
    ui->setupUi(this);

    setup();
    connectSlots();
}

PanelFrame::~PanelFrame()
{
    delete ui;
}

void PanelFrame::setup()
{
    QIcon iconClose = IconManager::instance().icon("chevron-right");
    QIcon iconOpen = IconManager::instance().icon("chevron-down");

    QStringList stylePreset = QStringList();
    stylePreset.append("No Style");

    // Blocks

    blockXYZLocation        = new BlockXYZLocation();
    blockXYZAdvanced        = new BlockXYZAdvanced();
    blockShape              = new BlockShape();
    blockFill               = new BlockFill();
    blockFillAdvanced       = new BlockFillAdvanced();
    blockStroke             = new BlockStroke();
    blockStrokeAdvanced     = new BlockStrokeAdvanced();
    blockDropShadow         = new BlockDropShadow();
    blockDropShadowAdvanced = new BlockDropShadowAdvanced();

    // Section
    ui->sectionXYZ->setCollapseIcons(iconClose, iconOpen);
    ui->sectionShape->setCollapseIcons(iconClose, iconOpen);
    ui->sectionFill->setCollapseIcons(iconClose, iconOpen);
    ui->sectionStroke->setCollapseIcons(iconClose, iconOpen);
    ui->sectionDropShadow->setCollapseIcons(iconClose, iconOpen);

    // Add custom elements in header
    QComboBox * comboFillStyle = new QComboBox();
    comboFillStyle->addItems(stylePreset);
    ui->sectionFill->addHeaderSuffixWidget(comboFillStyle);
    ui->sectionFill->addHeaderSuffixSpacing(8);

    QComboBox * comboStrokeStyle = new QComboBox();
    comboStrokeStyle->addItems(stylePreset);
    ui->sectionStroke->addHeaderSuffixWidget(comboStrokeStyle);
    ui->sectionStroke->addHeaderSuffixSpacing(8);


    // Add Menus
    addMenu(ui->sectionXYZ, blockXYZAdvanced);
    addMenu(ui->sectionFill, blockFillAdvanced);
    addMenu(ui->sectionStroke, blockStrokeAdvanced);
    addMenu(ui->sectionDropShadow, blockDropShadowAdvanced);


    // Add blocks
    ui->layoutXYZ->layout()->addWidget(blockXYZLocation);
    ui->layoutShape->layout()->addWidget(blockShape);
    ui->layoutFill->layout()->addWidget(blockFill);
    ui->layoutBorder->layout()->addWidget(blockStroke);
    ui->layoutDropShadow->layout()->addWidget(blockDropShadow);

//    FlowLayout *layoutPanel = new FlowLayout;
//    layoutPanel->addWidget(ui->sectionXYZ);
//    layoutPanel->addWidget(ui->sectionShape);
//    layoutPanel->addWidget(ui->sectionFill);
//    layoutPanel->addWidget(ui->sectionStroke);
//    layoutPanel->addWidget(ui->sectionDropShadow);
//    setLayout(layoutPanel);


//    // Test layout
//    FlowLayout *layoutXYZ = new FlowLayout;
//    layoutXYZ->addWidget(blockXYZLocation);
//    layoutXYZ->addWidget(blockXYZTransformation);
//    ui->layoutXYZ->setLayout(layoutXYZ);

//    FlowLayout *layoutShape = new FlowLayout;
//    layoutShape->addWidget(blockShape);
//    ui->layoutShape->setLayout(layoutShape);

//    FlowLayout *layoutFill = new FlowLayout;
//    layoutFill->addWidget(blockFill);
//    ui->layoutFill->setLayout(layoutFill);

//    FlowLayout *layoutBorder = new FlowLayout;
//    layoutBorder->addWidget(blockStroke);
//    ui->layoutBorder->setLayout(layoutBorder);

//    FlowLayout *layoutDropShadow = new FlowLayout;
//    layoutDropShadow->addWidget(blockDropShadow);
//    ui->layoutDropShadow->setLayout(layoutDropShadow);


}

void PanelFrame::connectSlots()
{

    connect(blockXYZLocation, &BlockXYZLocation::signalLockFrame, blockShape, &BlockShape::lockFrame);
    connect(blockXYZLocation, &BlockXYZLocation::signalLockSize, blockShape, &BlockShape::lockSize);

}
