#include "newdocument_dialog.h"
#include "listwidgetitem_delegate.h"
#include "ui_newdocument_dialog.h"
#include "icon_manager.h"
#include "enums.h"

/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

NewDocumentDialog::NewDocumentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDocumentDialog)
{
    ui->setupUi(this);

    orientationButtons = new QButtonGroup();

    setup();

    //   adjustSize();

    setWindowTitle( tr( "New Document" ) );
    setModal(true);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    setMaximumSize(sizeHint());

    connectSlots();

}

NewDocumentDialog::~NewDocumentDialog()
{
    delete ui;
}

void NewDocumentDialog::setup()
{

    // Facing
    ui->layoutFirstPage->setVisible(false);

    ui->componentPageSize->setMoveObjectsVisibility(false);

    dummyContent();

}

void NewDocumentDialog::connectSlots()
{
    connect(ui->listDocumentTypes, &QListWidget::itemSelectionChanged, this, &NewDocumentDialog::changedPageLayout);
}

/* ********************************************************************************* *
 *
 * Methods
 *
 * ********************************************************************************* */

void NewDocumentDialog::dummyContent()
{
    IconManager &iconManager = IconManager::instance();

    QIcon iconSingle = iconManager.icon("document-template-single");
    QIcon iconFaced = iconManager.icon("document-template-facing");
    QIcon icon3Fold = iconManager.icon("document-template-threefold");
    QIcon icon4Fold = iconManager.icon("document-template-fourfold");


    QListWidgetItem *itemSingle = new QListWidgetItem();
    itemSingle->setIcon(iconSingle);
    itemSingle->setText("Single");
    itemSingle->setData(Qt::UserRole, QVariant::fromValue(PageLayout::Single) );

    QListWidgetItem *itemFaced = new QListWidgetItem();
    itemFaced->setIcon(iconFaced);
    itemFaced->setText("Faced");
    itemFaced->setData(Qt::UserRole, QVariant::fromValue(PageLayout::Double) );

    QListWidgetItem *item3Fold = new QListWidgetItem();
    item3Fold->setIcon(icon3Fold);
    item3Fold->setText("3-Fold");
    item3Fold->setData(Qt::UserRole, QVariant::fromValue(PageLayout::ThreeFacing) );

    QListWidgetItem *item4Fold = new QListWidgetItem();
    item4Fold->setIcon(icon4Fold);
    item4Fold->setText("4-Fold");
    item4Fold->setData(Qt::UserRole, QVariant::fromValue(PageLayout::FourFacing) );



    ui->listDocumentTypes->setItemDelegate(new ListWidgetItemDelegate(48, ui->listDocumentTypes));
    ui->listDocumentTypes->addItem(itemSingle);
    ui->listDocumentTypes->addItem(itemFaced);
    ui->listDocumentTypes->addItem(item3Fold);
    ui->listDocumentTypes->addItem(item4Fold);

    ui->listDocumentTypes->setCurrentItem(itemSingle);

}

/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

void NewDocumentDialog::changedPageLayout()
{
    PageLayout m_pageLayout = static_cast<PageLayout>(ui->listDocumentTypes->selectedItems()[0]->data(Qt::UserRole).toInt());
    IconManager &iconManager = IconManager::instance();

    ui->comboFirstPage->setPageLayout(m_pageLayout);

    if(m_pageLayout == PageLayout::Single){
        ui->layoutFirstPage->setVisible( false );

        ui->componentMargins->componentSpaceInput()->layoutLeft()->setPixmap( iconManager.pixmap("space-left") );
        ui->componentMargins->componentSpaceInput()->layoutRight()->setPixmap( iconManager.pixmap("space-right") );

        ui->componentBleeds->layoutLeft()->setPixmap( iconManager.pixmap("space-left") );
        ui->componentBleeds->layoutRight()->setPixmap( iconManager.pixmap("space-right") );
    }else{
        ui->layoutFirstPage->setVisible( true );

        ui->componentMargins->componentSpaceInput()->layoutLeft()->setPixmap( iconManager.pixmap("space-inside") );
        ui->componentMargins->componentSpaceInput()->layoutRight()->setPixmap( iconManager.pixmap("space-outside") );

        ui->componentBleeds->layoutLeft()->setPixmap( iconManager.pixmap("space-inside") );
        ui->componentBleeds->layoutRight()->setPixmap( iconManager.pixmap("space-outside") );
    }

}



void NewDocumentDialog::accept()
{
    qDebug() << "[clicked] create new document";

    this->close();
}
