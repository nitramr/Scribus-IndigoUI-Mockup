#include "panel_layers.h"
#include "iconmanager.h"
#include "ui_panel_layers.h"
#include <QCheckBox>
#include <QPainter>

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

PanelLayers::PanelLayers(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PanelLayers)
{
    ui->setupUi(this);

    setup();
    rebuildList();
}

PanelLayers::~PanelLayers()
{
    delete ui;
}

void PanelLayers::setup()
{
    IconManager &iconManager = IconManager::instance();

    ui->buttonNewLayer->setIcon(iconManager.icon("add"));
    ui->buttonDeleteLayer->setIcon(iconManager.icon("remove"));
    ui->buttonDuplicateLayer->setIcon(iconManager.icon("copy"));
    ui->buttonRaiseLayer->setIcon(iconManager.icon("layer-up"));
    ui->buttonLowerLayer->setIcon(iconManager.icon("layer-down"));


    //ui->tableLayers = new QTableWidget(0, 8, this );
    ui->tableLayers->setColumnCount(8);
    ui->tableLayers->setRowCount(0);

    ui->tableLayers->setHorizontalHeaderItem(0, new QTableWidgetItem(""));
    ui->tableLayers->setHorizontalHeaderItem(1, new QTableWidgetItem(iconManager.icon("layer-visible"), ""));
    ui->tableLayers->setHorizontalHeaderItem(2, new QTableWidgetItem(iconManager.icon("layer-print"), ""));
    ui->tableLayers->setHorizontalHeaderItem(3, new QTableWidgetItem(iconManager.icon("layer-lock"), ""));
    ui->tableLayers->setHorizontalHeaderItem(4, new QTableWidgetItem(iconManager.icon("layer-wrap"), ""));
    ui->tableLayers->setHorizontalHeaderItem(5, new QTableWidgetItem(iconManager.icon("layer-outline"), ""));
    ui->tableLayers->setHorizontalHeaderItem(6, new QTableWidgetItem(iconManager.icon("layer-selection"), ""));
    ui->tableLayers->setHorizontalHeaderItem(7, new QTableWidgetItem( tr("Name")));

    ui->tableLayers->setColumnWidth(0, 24);
    ui->tableLayers->setColumnWidth(1, 24);
    ui->tableLayers->setColumnWidth(2, 24);
    ui->tableLayers->setColumnWidth(3, 24);
    ui->tableLayers->setColumnWidth(4, 24);
    ui->tableLayers->setColumnWidth(5, 24);
    ui->tableLayers->setColumnWidth(6, 24);
    ui->tableLayers->setSortingEnabled(false);
    ui->tableLayers->setSelectionBehavior( QAbstractItemView::SelectRows );

    //QHeaderView *header = ui->tableLayers->horizontalHeader();
    ui->tableLayers->horizontalHeader()->setStretchLastSection(true);
    ui->tableLayers->horizontalHeader()->setSectionsClickable(false );
    ui->tableLayers->horizontalHeader()->setSectionsMovable( false );
    ui->tableLayers->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableLayers->horizontalHeader()->setHighlightSections(false);
    ui->tableLayers->horizontalHeader()->setMaximumSectionSize(24);

   // QHeaderView *Header = ui->tableLayers->verticalHeader();
    ui->tableLayers->verticalHeader()->setSectionsMovable( false );
    ui->tableLayers->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableLayers->verticalHeader()->hide();


    layers = new ScLayers();
    layers->addLayer("Background");


}




/* ********************************************************************************* *
 *
 * Private Functions
 *
 * ********************************************************************************* */

void PanelLayers::rebuildList()
{

    // See original here: https://github.com/scribusproject/scribus/blob/master/scribus/ui/layers.cpp
    // For demo purpose some values are hard coded


    QString tmp;
    //        int layerCount = m_Doc->layerCount();
    int layerCount = 1;
    ui->tableLayers->setRowCount(layerCount);

    for (auto it = layers->begin(); it != layers->end(); ++it)
    {
        int layerID = it->ID;
        //TODO once "layers" is not set anymore, need to get layer number differently
        //            int layerLevel = m_Doc->layerLevelFromID(layerID);
        int layerLevel = 0;
        tmp.setNum(layerLevel);
        int row = layerCount-layerLevel - 1;
        QToolButton *pb = new QToolButton(ui->tableLayers);
        pb->setObjectName(tmp);
        pb->setAutoRaise(true);
        pb->setText( "" );
        QPixmap pm(20,16);
        //            pm.fill(m_Doc->layerMarker(layerID));
        QPainter painter(&pm);
        painter.setBrush(Qt::black);
        painter.setPen(palette().color(QPalette::Mid));
        painter.drawRect(pm.rect().adjusted(0,0,-1,-1));
        painter.end();
        pb->setIcon(pm);
        ui->tableLayers->setCellWidget(row, 0, pb);
        //connect(pb, SIGNAL(clicked()), this, SLOT(markLayer()));

        QWidget *cw1 = new QWidget(ui->tableLayers);
        QCheckBox *cp1 = new QCheckBox(cw1);
        cp1->setObjectName(tmp);
        QHBoxLayout *cl1 = new QHBoxLayout(cw1);
        cl1->addWidget(cp1);
        cl1->setAlignment(Qt::AlignCenter);
        cl1->setContentsMargins(0, 0, 0, 0);
        ui->tableLayers->setCellWidget(row, 1, cw1);
        //            cp1->setChecked(m_Doc->layerVisible(layerID));
        cp1->setChecked(true);
        //connect(cp1, SIGNAL(clicked()), this, SLOT(visibleLayer()));

        QWidget *cw2 = new QWidget(ui->tableLayers);
        QCheckBox *cp2 = new QCheckBox(cw2);
        cp2->setObjectName(tmp);
        //            cp2->setChecked(m_Doc->layerPrintable(layerID));
        cp2->setChecked(true);
        QHBoxLayout *cl2 = new QHBoxLayout(cw2);
        cl2->addWidget(cp2);
        cl2->setAlignment(Qt::AlignCenter);
        cl2->setContentsMargins(0, 0, 0, 0);
        ui->tableLayers->setCellWidget(row, 2, cw2);
        //connect(cp2, SIGNAL(clicked()), this, SLOT(printLayer()));

        QWidget *cw3 = new QWidget(ui->tableLayers);
        QCheckBox *cp3 = new QCheckBox(cw3);
        cp3->setObjectName(tmp);
        //            cp3->setChecked(m_Doc->layerLocked(layerID));
        cp3->setChecked(false);
        QHBoxLayout *cl3 = new QHBoxLayout(cw3);
        cl3->addWidget(cp3);
        cl3->setAlignment(Qt::AlignCenter);
        cl3->setContentsMargins(0, 0, 0, 0);
        ui->tableLayers->setCellWidget(row, 3, cw3);
        //connect(cp3, SIGNAL(clicked()), this, SLOT(lockLayer()));

        QWidget *cw4 = new QWidget(ui->tableLayers);
        QCheckBox *cp4 = new QCheckBox(cw4);
        cp4->setObjectName(tmp);
        //            cp4->setChecked(m_Doc->layerFlow(layerID));
        cp4->setChecked(true);
        QHBoxLayout *cl4 = new QHBoxLayout(cw4);
        cl4->addWidget(cp4);
        cl4->setAlignment(Qt::AlignCenter);
        cl4->setContentsMargins(0, 0, 0, 0);
        ui->tableLayers->setCellWidget(row, 4, cw4);
        //connect(cp4, SIGNAL(clicked()), this, SLOT(flowToggleLayer()));

        QWidget *cw5 = new QWidget(ui->tableLayers);
        QCheckBox *cp5 = new QCheckBox(cw5);
        cp5->setObjectName(tmp);
        //            cp5->setChecked(m_Doc->layerOutline(layerID));
        cp5->setChecked(false);
        QHBoxLayout *cl5 = new QHBoxLayout(cw5);
        cl5->addWidget(cp5);
        cl5->setAlignment(Qt::AlignCenter);
        cl5->setContentsMargins(0, 0, 0, 0);
        ui->tableLayers->setCellWidget(row, 5, cw5);
        //connect(cp5, SIGNAL(clicked()), this, SLOT(outlineToggleLayer()));

        QWidget *cw6 = new QWidget(ui->tableLayers);
        QCheckBox *cp6 = new QCheckBox(cw6);
        cp6->setObjectName(tmp);
        //            cp6->setChecked(m_Doc->layerSelectable(layerID));
        cp6->setChecked(false);
        QHBoxLayout *cl6 = new QHBoxLayout(cw6);
        cl6->addWidget(cp6);
        cl6->setAlignment(Qt::AlignCenter);
        cl6->setContentsMargins(0, 0, 0, 0);
        ui->tableLayers->setCellWidget(row, 6, cw6);
        //connect(cp6, SIGNAL(clicked()), this, SLOT(selectToggleLayer()));

        //            ui->tableLayers->setItem(row, 7, new QTableWidgetItem(m_Doc->layerName(layerID)));
        ui->tableLayers->setItem(row, 7, new QTableWidgetItem("Background"));
    }

}
