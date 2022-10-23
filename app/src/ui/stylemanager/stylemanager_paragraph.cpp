#include "stylemanager_paragraph.h"
#include "ui_stylemanager_paragraph.h"

StyleManagerParagraph::StyleManagerParagraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StyleManagerParagraph)
{
    ui->setupUi(this);

    setup();
}

StyleManagerParagraph::~StyleManagerParagraph()
{
    delete ui;
}

void StyleManagerParagraph::setup()
{

}
