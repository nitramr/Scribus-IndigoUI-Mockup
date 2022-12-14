#include "panel_toolproperties.h"
#include "block_fill.h"
#include "block_stroke.h"
#include "block_xyz_location.h"
#include "flow_layout/flow_layout.h"
#include "qpushbutton.h"
#include "ui_panel_toolproperties.h"

#include <QFrame>

PanelToolProperties::PanelToolProperties(QWidget *parent) :
    Panel(parent),
    ui(new Ui::PanelToolProperties)
{
    ui->setupUi(this);

    setup();
}

PanelToolProperties::~PanelToolProperties()
{
    delete ui;
}

void PanelToolProperties::setup()
{

    BlockXYZLocation *blockXZYLocation = new BlockXYZLocation();

    this->layout()->addWidget(blockXZYLocation);

//    BlockFill * blockFill = new BlockFill();
//    BlockStroke * blockStroke = new BlockStroke();

//    QFrame *line = new QFrame();
//    line->setFrameShape(QFrame::VLine);
//    line->setFrameShadow(QFrame::Sunken);
//    line->setLineWidth(1);
//    line->setMinimumHeight(100);

//    QFrame *line2 = new QFrame();
//    line2->setFrameShape(QFrame::VLine);
//    line2->setFrameShadow(QFrame::Sunken);
//    line2->setLineWidth(1);
//    line2->setMinimumHeight(100);

//    QFrame *line3 = new QFrame();
//    line3->setFrameShape(QFrame::VLine);
//    line3->setFrameShadow(QFrame::Sunken);
//    line3->setLineWidth(1);
//    line3->setMinimumHeight(100);


//    FlowLayout *flowLayout = new FlowLayout;
//    flowLayout->addWidget(blockXZYLocation);
//    flowLayout->addWidget(line);
//    flowLayout->addWidget(line2);
//    flowLayout->addWidget(blockFill);
//    flowLayout->addWidget(line3);
//    flowLayout->addWidget(blockStroke);

//    setLayout(flowLayout);

}
