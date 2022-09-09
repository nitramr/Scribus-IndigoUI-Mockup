#include "dock_documentbase.h"

#include "dummydocument.h"
#include "icon_manager.h"

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include <color_button.h>
#include "anglepicker.h"
#include "formwidget.h"
#include "basepoint_widget.h"
#include "colormap.h"
#include "colorpicker_color.h"
#include "colorslider.h"
#include "colorwheel.h"
#include "colorblind.h"
#include <QButtonGroup>
#include <QPainterPath>
#include <QMenu>
#include <QToolBar>
#include <QtColorWidgets/HarmonyColorWheel>
#include <QtColorWidgets/color_wheel.hpp>

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

DockDocumentBase::DockDocumentBase(const QString &title, QWidget *parent) : ads::CDockWidget(title, parent)
{
    setFeature(ads::CDockWidget::DockWidgetFloatable, false);
    setFeature(ads::CDockWidget::DockWidgetMovable, false);
    setFeature(ads::CDockWidget::DockWidgetDeleteOnClose, true);

    setIcon(IconManager::instance().icon("file-document"));
    setContextMenuPolicy(Qt::CustomContextMenu);

    dialogManagePageProperties = new ManagePagePropertiesDialog(this);
    m_contextMenu = new QMenu(this);
    dummyDoc = new DummyDocument();

    buttonText = new QToolButton();
    buttonText->setText("Text");
    buttonText->setCheckable(true);
    buttonText->setChecked(true);
    buttonImage = new QToolButton();
    buttonImage->setText("Image");
    buttonImage->setCheckable(true);
    buttonTable = new QToolButton();
    buttonTable->setText("Table");
    buttonTable->setCheckable(true);

    buttonGroupContentToggle = new QButtonGroup();
    buttonGroupContentToggle->addButton(buttonText, 0);
    buttonGroupContentToggle->addButton(buttonImage, 1);
    buttonGroupContentToggle->addButton(buttonTable, 2);


    setup();
    connectSlots();
}

void DockDocumentBase::setup()
{

    setupContextMenu();
    dummyContent();

}

void DockDocumentBase::connectSlots()
{

    connect(this, &DockDocumentBase::customContextMenuRequested, this, &DockDocumentBase::showContextMenu);

    // Dummy
    connect(buttonGroupContentToggle, &QButtonGroup::idClicked, this, &DockDocumentBase::changeContentMode);
}


/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

void DockDocumentBase::showContextMenu(const QPoint &pos)
{
    m_contextMenu->exec(mapToGlobal(pos));
}

void DockDocumentBase::showManagePageDialog()
{
    if(dialogManagePageProperties->exec()){

    }

}

void DockDocumentBase::changeContentMode(int id)
{
    switch(id){
    case 0:
        emit changedContentMode(PanelContent::ContentMode::Text);
        break;
    case 1:
        emit changedContentMode(PanelContent::ContentMode::Image);
        break;
    case 2:
        emit changedContentMode(PanelContent::ContentMode::Table);
        break;
    }
}

/* ********************************************************************************* *
 *
 * Private Methods
 *
 * ********************************************************************************* */

void DockDocumentBase::setupContextMenu()
{
    QAction *actionShowGrid = new QAction( tr("Show Grid") );
    actionShowGrid->setCheckable(true);
    actionShowGrid->setChecked(true);
    connect(actionShowGrid, &QAction::triggered, dummyDoc, &DummyDocument::toggleGridVisibility);

    QAction *actionShowBaseline = new QAction( tr("Show Baseline") );
    actionShowBaseline->setCheckable(true);
    actionShowBaseline->setChecked(true);
    connect(actionShowBaseline, &QAction::triggered, dummyDoc, &DummyDocument::toggleBaselineVisibility);

    QAction *actionShowGuides = new QAction( tr("Show Guides") );
    actionShowGuides->setCheckable(true);
    actionShowGuides->setChecked(true);
    connect(actionShowGuides, &QAction::triggered, dummyDoc, &DummyDocument::toggleGuideVisibility);


    m_contextMenu->addAction(actionShowGrid);
    m_contextMenu->addAction(actionShowBaseline);
    m_contextMenu->addAction(actionShowGuides);
    m_contextMenu->addSeparator();
    m_contextMenu->addAction( tr("Manage Page Properties..."), this, &DockDocumentBase::showManagePageDialog );
}

void DockDocumentBase::dummyContent()
{       
    IconManager &iconManager = IconManager::instance();

    QToolBar *toolBar = new QToolBar();
    toolBar->setIconSize(QSize(16,16));
    toolBar->addAction(iconManager.icon("test1"), "Test1");
    toolBar->addAction(iconManager.icon("test2"), "Test2");
    toolBar->addAction(iconManager.icon("test3"), "Test3");
    toolBar->addAction(iconManager.icon("test4"), "Test4");
    toolBar->addAction(iconManager.icon("test5"), "Test5");
    toolBar->addAction(iconManager.icon("test6"), "Test6");

    toolBar->addAction(iconManager.icon("test"), "Test");
    toolBar->addAction(iconManager.icon("testPNG"), "Test");
    toolBar->addAction(iconManager.icon("testFill"), "Test");
    QPainterPath path;
    path.addEllipse(0,0,48,48);
    IconManager::instance().addIcon("testPath", path);
    toolBar->addAction(iconManager.icon("testPath"), "Rendered path");
    toolBar->addAction(iconManager.icon("color-cmyk"), "CMK");
    toolBar->addAction(iconManager.icon("color-rgb"), "RGB");
    toolBar->addAction(iconManager.icon("color-lab"), "Lab");
    toolBar->addWidget(buttonText);
    toolBar->addWidget(buttonImage);
    toolBar->addWidget(buttonTable);


    QGridLayout *layGrid = new QGridLayout();
    layGrid->setContentsMargins(0,0,0,0);
    layGrid->addWidget(dummyDoc, 1,1);
    layGrid->addWidget(toolBar, 2,1);



    QWidget *dummy = new QWidget();
    dummy->setLayout(layGrid);
    setWidget(dummy);
}





