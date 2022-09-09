#include "component_documentselector.h"
#include "ui_component_documentselector.h"
#include "icon_manager.h"
#include "file_utils.h"
#include "configuration_manager.h"
#include "newdocument_dialog.h"

#include <QStringListModel>
#include <listwidgetitem_delegate.h>

ComponentDocumentSelector::ComponentDocumentSelector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::componentDocumentSelector)
{
    ui->setupUi(this);

    connectSlots();

    dummyContent();
}

ComponentDocumentSelector::~ComponentDocumentSelector()
{
    delete ui;
}

void ComponentDocumentSelector::dummyContent()
{

    QIcon icon = FileUtils::mimeIconFromFile("test.sla");


    QListWidgetItem *item = new QListWidgetItem();
    item->setIcon(icon);
    item->setText("My Document.sla");

    QListWidgetItem *item2 = new QListWidgetItem();
    item2->setIcon(icon);
    item2->setText("New Document.sla");


    ui->listWidget->setItemDelegate(new ListWidgetItemDelegate(64, ui->listWidget));
    ui->listWidget->addItem(item);
    ui->listWidget->addItem(item2);

}

void ComponentDocumentSelector::connectSlots()
{
    connect(ui->buttonNew, &QPushButton::clicked, this, &ComponentDocumentSelector::newDocument);
    connect(ui->buttonOpen, &QPushButton::clicked, this, &ComponentDocumentSelector::openDocument);
    connect(ui->buttonTemplate, &QPushButton::clicked, this, &ComponentDocumentSelector::documentFromTemplate);
}

void ComponentDocumentSelector::newDocument()
{
    NewDocumentDialog *newDocumentDialog = new NewDocumentDialog(this);

    if(newDocumentDialog->exec()){

    }

}

void ComponentDocumentSelector::openDocument()
{
    qDebug() << "DocumentSelector::openDocument()";
}

void ComponentDocumentSelector::documentFromTemplate()
{
    qDebug() << "DocumentSelector::documentFromTemplate()";
}
