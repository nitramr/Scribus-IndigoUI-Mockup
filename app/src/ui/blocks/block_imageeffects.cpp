#include "block_imageeffects.h"
#include "imageeffects/imageeffect_item.h"
#include "sectioncontainer.h"
#include "ui_block_imageeffects.h"

/* ********************************************************************************* *
 *
 * Constructor & Setup
 *
 * ********************************************************************************* */

BlockImageEffects::BlockImageEffects(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockImageEffects)
{
    ui->setupUi(this);
    setup();
}

BlockImageEffects::~BlockImageEffects()
{
    delete ui;
}

void BlockImageEffects::setup()
{

    // https://akshaybabloo.medium.com/creating-custom-widget-for-qlistwidget-in-qt-6-3ae03f051906

    for(int i = 1; i < 5; ++i){

        //QLabel label("Label" + QString::number(i));

        auto widget = new ImageEffectItem("Effect " + QString::number(i));
        widget->setHasStyle(false);
        auto item = new QListWidgetItem();
        item->setSizeHint(widget->sizeHint());
        item->setBackground(palette().color(QPalette::Window));

        ui->listEffects->addItem(item);
        ui->listEffects->setItemWidget(item, widget);

       // ui->listEffects->addItem(new QListWidgetItem(QString("Item %1").arg(i)));
    }


    QPalette palette;
    palette.setColor(QPalette::Highlight, ui->listEffects->palette().color(QPalette::Window));
    palette.setColor(QPalette::HighlightedText, ui->listEffects->palette().color(QPalette::WindowText));
    ui->listEffects->setPalette(palette);

    ui->listEffects->setDragDropMode(QAbstractItemView::InternalMove);
    ui->listEffects->setFocusPolicy(Qt::NoFocus);
    ui->listEffects->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
//    ui->listEffects->setFixedSize(ui->listEffects->sizeHintForColumn(0) + ui->listEffects->frameWidth() * 2, ui->listEffects->sizeHintForRow(0) * ui->listEffects->count() + 2 * ui->listEffects->frameWidth());
//    ui->listEffects->setFixedHeight( ui->listEffects->sizeHintForRow(0) * ui->listEffects->count() + 2 * ui->listEffects->frameWidth() );
//    ui->listEffects->setSelectionMode(QAbstractItemView::SingleSelection);
//    ui->listEffects->setSizeAdjustPolicy(QListWidget::AdjustToContents);

    // #########################


//    for(int i = 1; i < 5; ++i){

//       // QLabel label("Label" + QString::number(i));

//        auto widget = new ImageEffectItem(i);
//       // widget->addPage(&label);
//        auto item = new QTreeWidgetItem();
//        auto childItem = new QTreeWidgetItem();

//        item->setSizeHint(0, widget->sizeHint());
//        item->setBackground(0, palette().color(QPalette::Window));
//        item->addChild(childItem);
//        ui->treeEffects->addTopLevelItem(item);
//        ui->treeEffects->setItemWidget(childItem, 0, widget);

//       // ui->listEffects->addItem(new QListWidgetItem(QString("Item %1").arg(i)));
//    }


////    QPalette palette;
////    palette.setColor(QPalette::Highlight, ui->listEffects->palette().color(QPalette::Window));
////    palette.setColor(QPalette::HighlightedText, ui->listEffects->palette().color(QPalette::WindowText));
////    ui->treeEffects->setPalette(palette);


////    ui->treeEffects->setFocusPolicy(Qt::NoFocus);
//    ui->treeEffects->setColumnCount(2);
//    ui->treeEffects->setSelectionMode(QAbstractItemView::MultiSelection);
//    ui->treeEffects->setSelectionBehavior(QAbstractItemView::SelectRows);
//    ui->treeEffects->setContextMenuPolicy(Qt::CustomContextMenu);
//    ui->treeEffects->setEditTriggers(QAbstractItemView::NoEditTriggers);
////    ui->treeEffects->setItemsExpandable(false);
//    ui->treeEffects->setExpandsOnDoubleClick(false);

//    ui->treeEffects->setDragEnabled(true);
//        ui->treeEffects->viewport()->setAcceptDrops(true);
//        ui->treeEffects->setDropIndicatorShown(true);
//        ui->treeEffects->setDragDropMode(QAbstractItemView::InternalMove);

////    ui->listEffects->setFixedSize(ui->listEffects->sizeHintForColumn(0) + ui->listEffects->frameWidth() * 2, ui->listEffects->sizeHintForRow(0) * ui->listEffects->count() + 2 * ui->listEffects->frameWidth());
////    ui->treeEffects->setFixedHeight( ui->listEffects->sizeHintForRow(0) * ui->listEffects->count() + 2 * ui->listEffects->frameWidth() );




}

/* ********************************************************************************* *
 *
 * Constructor & Setup
 *
 * ********************************************************************************* */
