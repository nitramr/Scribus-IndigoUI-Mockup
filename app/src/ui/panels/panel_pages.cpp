#include "panel_pages.h"
#include <QPainter>
#include "dialog_newpage.h"
#include "ui_panel_pages.h"

#include "pagelist.h"
#include "iconmanager.h"
#include "commonstrings.h"


// Reference:
// https://github.com/scribusproject/scribus/blob/master/scribus/ui/pagepalette_pages.cpp
// https://github.com/scribusproject/scribus/blob/master/scribus/ui/pagelayout.cpp


/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

PanelPages::PanelPages(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PanelPages)
{
    ui->setupUi(this);

    dialogInsertPage = new DialogNewPage(this);
    dialogDuplicatePage = new DialogDuplicatePage(this);
    dialogMovePage = new DialogMovePage(this);
    dialogNewParentPage = new DialogNewParentPage(this);
    dialogImportPage = new DialogImportPage(this);
    dialogImportParentPage = new DialogImportParentPage(this);

    setup();
    connectSlots();
}

PanelPages::~PanelPages()
{
    delete ui;
}


void PanelPages::setup()
{

    IconManager &iconManager = IconManager::instance();

    QIcon iconClose = iconManager.icon("chevron-right");
    QIcon iconOpen = iconManager.icon("chevron-down");



    // Section
    ui->sectionParentPages->setCollapseIcons(iconClose, iconOpen);
    ui->sectionDocumentPages->setCollapseIcons(iconClose, iconOpen);

    // Page Viewer
    ui->viewDocumentPages->pageGrid()->setTileSize(64);
    ui->viewDocumentPages->pageGrid()->setPageOrientation(Qt::Vertical);

    // Page Viewer (Comboboxes)
    ui->comboDocumentLayout->addItem(iconManager.icon("page-type-single"), "Single", QVariant::fromValue(PageLayout::Single));
    ui->comboDocumentLayout->addItem(iconManager.icon("page-type-facing"), "Facing", QVariant::fromValue(PageLayout::Double));
    ui->comboDocumentLayout->addItem(iconManager.icon("page-type-threefold"), "3-Fold", QVariant::fromValue(PageLayout::ThreeFacing));
    ui->comboDocumentLayout->addItem(iconManager.icon("page-type-fourfold"), "4-Fold", QVariant::fromValue(PageLayout::FourFacing));

    ui->layoutFirstPage->setVisible(false);

    // Page Viewer (Buttons)
    ui->buttonAddPage->setIcon(iconManager.icon("page-add"));
    ui->buttonImportPage->setIcon(iconManager.icon("page-import"));
    ui->buttonDuplicatePage->setIcon(iconManager.icon("page-duplicate"));
    ui->buttonMovePage->setIcon(iconManager.icon("page-move"));
    //    ui->buttonDeletePage->setIcon(iconManager.icon("page-delete"));

    // Parent View (Buttons)
    ui->buttonAddParent->setIcon(iconManager.icon("page-add"));
    ui->buttonImportParent->setIcon(iconManager.icon("page-import"));
    ui->buttonDuplicateParent->setIcon(iconManager.icon("page-duplicate"));
    //    ui->buttonDeleteParent->setIcon(iconManager.icon("page-delete"));







    // ----------- Dummy Document Pages ------------------------
    //QPixmap tile(":/images/splashscreen");
    QRect pageRect(0,0,96,96);
    QPixmap tile(pageRect.size());

    //    QLinearGradient paperFill(pageRect.topLeft(), pageRect.bottomLeft());
    //    paperFill.setColorAt(0, Qt::white);
    //    paperFill.setColorAt(1, QColor::fromHslF(0,0,0.8) );

    QPainter painter;
    painter.begin(&tile);
    painter.fillRect(pageRect, Qt::white);

    // 9999 pages ~ 130ms render time with images
    for(int i = 0; i < 20; i++){

        PageCell* page = new PageCell("Normal", i, tile);
        ui->viewDocumentPages->pageGrid()->pageList()->append( page );

    }

    ui->viewDocumentPages->pageGrid()->setSelectedPage(0);

    // ----------- Dummy Parent Pages ------------------------

    QPixmap pm;
    QListWidgetItem* item;

    QMap<QString,int> MasterNames;
    MasterNames.insert("Normal", 0);
    MasterNames.insert("Normal Left", 1);

    for (auto it = MasterNames.cbegin(); it != MasterNames.cend(); ++it)
    {
        const QString& pageName = it.key();
        QString pageLabel = (pageName == CommonStrings::masterPageNormal) ? CommonStrings::trMasterPageNormal : pageName;
        if (ui->listParentPages->m_thumb)
        {
            //pm = QPixmap::fromImage(currView->MPageToPixmap(pageName, 60));
            pm = QPixmap(":/images/splashscreen");
            item = new QListWidgetItem(QIcon(pm), pageLabel, ui->listParentPages);
        }
        else
            item = new QListWidgetItem(pageLabel, ui->listParentPages);
        item->setData(Qt::UserRole, pageName);
    }

}

void PanelPages::connectSlots()
{
    // Page Viewer
    connect(ui->viewDocumentPages->pageGrid(), &PageGrid::UseTemp, this, &PanelPages::useTemplate);
    connect(ui->viewDocumentPages->pageGrid(), &PageGrid::NewPage, this, &PanelPages::newPage);
    connect(ui->viewDocumentPages->pageGrid(), &PageGrid::movePage, this, &PanelPages::movePage);
    connect(ui->viewDocumentPages->pageGrid(), &PageGrid::Click, this, &PanelPages::click);
    connect(ui->viewDocumentPages->pageGrid(), &PageGrid::delPageRequest, this, &PanelPages::delPageRequest);

    // Page Viewer Comboboxes
    connect(ui->comboDocumentLayout, &QComboBox::currentIndexChanged, this, &PanelPages::changeDocumentLayout);
    connect(ui->comboFirstPage, &QComboBox::currentIndexChanged, this, &PanelPages::changeFirstPage);

    // Buttons Page
    connect(ui->buttonAddPage, &QToolButton::pressed, this, &PanelPages::showAddPageDialog);
    connect(ui->buttonDuplicatePage, &QToolButton::pressed, this, &PanelPages::showDuplicatePageDialog);
    connect(ui->buttonMovePage, &QToolButton::pressed, this, &PanelPages::showMovePageDialog);
    connect(ui->buttonImportPage, &QToolButton::pressed, this, &PanelPages::showImportPageDialog);


    // Buttons Parent
    connect(ui->buttonAddParent, &QToolButton::pressed, this, &PanelPages::showNewParentPageDialog);
    connect(ui->buttonDuplicateParent, &QToolButton::pressed, this, &PanelPages::showNewParentPageDialog);
    connect(ui->buttonImportParent, &QToolButton::pressed, this, &PanelPages::showImportParentPageDialog);

    // Labels
    connect(ui->labelDeletePage, &TrashBin::delPageRequest, this, &PanelPages::delPageRequest);
    connect(ui->labelDeleteParentPage, &TrashBin::delMasterRequest, this, &PanelPages::delParentRequest);

    connect(ui->sectionDocumentPages, &SectionContainer::collapsedState, this, &PanelPages::updateLayout);

}

void PanelPages::updateLayout(bool isCollapsed)
{

    if(!isCollapsed){
        ui->sectionDocumentPages->setSizePolicy(ui->sectionDocumentPages->sizePolicy().horizontalPolicy(), QSizePolicy::Expanding);
        ui->verticalSpacer->changeSize(this->width(), 0, ui->verticalSpacer->sizePolicy().horizontalPolicy(), QSizePolicy::Maximum );
    }else{
        ui->sectionDocumentPages->setSizePolicy(ui->sectionDocumentPages->sizePolicy().horizontalPolicy(), QSizePolicy::Maximum);
        ui->verticalSpacer->changeSize(this->width(), this->height(), ui->verticalSpacer->sizePolicy().horizontalPolicy(), QSizePolicy::Expanding );
    }

}

/* ********************************************************************************* *
 *
 * Functions
 *
 * ********************************************************************************* */



/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */
void PanelPages::useTemplate(int pageId, QString parentPage)
{
    qDebug() << QString("PanelPages::useTemplate: pageId %1, parentPage %2").arg(QString::number(pageId), parentPage);
}

void PanelPages::newPage(int pageId, QString parentPage)
{
    qDebug() << QString("PanelPages::newPage: id %1, parentPage %2").arg(QString::number(pageId), parentPage);
}

void PanelPages::movePage(int oldId, int newId)
{
    qDebug() << QString("PanelPages::movePage: oldID %1, newID %2").arg(QString::number(oldId), QString::number(newId));
}

void PanelPages::click(int row, int column, int button)
{
    qDebug() << QString("PanelPages::click: row %1, column %2, button %3").arg(QString::number(row), QString::number(column), QString::number(button));
}

void PanelPages::delPageRequest(int pageId)
{
    qDebug() << QString("PanelPages::delPageRequest: ID %1").arg(QString::number(pageId));
}

void PanelPages::delParentRequest(QString parentPage)
{
    qDebug() << QString("PanelPages::delParentRequest: Name %1").arg(parentPage);
}

void PanelPages::showAddPageDialog()
{

    if (dialogInsertPage->exec())
    {

    }

}

void PanelPages::showDuplicatePageDialog()
{
    if (dialogDuplicatePage->exec())
    {

    }
}

void PanelPages::showMovePageDialog()
{
    if (dialogMovePage->exec())
    {

    }
}

void PanelPages::showImportPageDialog()
{
    if (dialogImportPage->exec())
    {

    }
}

void PanelPages::showNewParentPageDialog()
{
    if (dialogNewParentPage->exec())
    {

    }
}

void PanelPages::showImportParentPageDialog()
{
    if (dialogImportParentPage->exec())
    {

    }
}

void PanelPages::changeDocumentLayout()
{
    PageLayout m_pageLayout = static_cast<PageLayout>(ui->comboDocumentLayout->currentData(Qt::UserRole).toInt());

    ui->viewDocumentPages->pageGrid()->setPageLayout(m_pageLayout);
    ui->comboFirstPage->setPageLayout(m_pageLayout);
    ui->layoutFirstPage->setVisible( m_pageLayout == PageLayout::Single ? false : true );

    dialogInsertPage->setPageLayout(m_pageLayout);
    dialogNewParentPage->setPageLayout(m_pageLayout);


}

void PanelPages::changeFirstPage()
{
    FirstPage m_firstpage = static_cast<FirstPage>(ui->comboFirstPage->currentData(Qt::UserRole).toInt());

    switch(m_firstpage){
    case FirstPage::Left:
        ui->viewDocumentPages->pageGrid()->setPageOffset(0);
        break;
    case FirstPage::MiddleLeft:
    case FirstPage::Middle:
        ui->viewDocumentPages->pageGrid()->setPageOffset(1);
        break;
    case FirstPage::MiddleRight:
        ui->viewDocumentPages->pageGrid()->setPageOffset(2);
        break;
    case FirstPage::Right:

        switch(ui->viewDocumentPages->pageGrid()->pageLayout()){
        case PageLayout::Single:
            break;
        case PageLayout::Double:
            ui->viewDocumentPages->pageGrid()->setPageOffset(1);
            break;
        case PageLayout::ThreeFacing:
            ui->viewDocumentPages->pageGrid()->setPageOffset(2);

            break;
        case PageLayout::FourFacing:
            ui->viewDocumentPages->pageGrid()->setPageOffset(3);
            break;
        }

        break;
    }


}
