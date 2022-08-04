#include "panel_outliner.h"
#include "ui_panel_outliner.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

PanelOutliner::PanelOutliner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PanelOutliner)
{
    ui->setupUi(this);

    setup();
}

PanelOutliner::~PanelOutliner()
{
    delete ui;
}

void PanelOutliner::setup()
{
    ui->reportDisplay->setRootIsDecorated( true );
    ui->reportDisplay->setColumnCount(1);
    ui->reportDisplay->setHeaderLabel( tr("Element"));
    ui->reportDisplay->header()->setSectionsClickable(false );
    ui->reportDisplay->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->reportDisplay->setSortingEnabled(false);
    ui->reportDisplay->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->reportDisplay->setContextMenuPolicy(Qt::CustomContextMenu);
}
