#include "panel_content.h"
#include "ui_panel_content.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

PanelContent::PanelContent(QWidget *parent) :
    Panel(parent),
    ui(new Ui::PanelContent)
{
    ui->setupUi(this);

    setup();
    setContentMode(ContentMode::Text);
}

PanelContent::~PanelContent()
{
    delete ui;
}



void PanelContent::setup()
{

}

/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

void PanelContent::setContentMode(ContentMode mode)
{
    m_contentMode = mode;

    switch(m_contentMode){
    case ContentMode::Text:
        ui->contentText->setVisible(true);
        ui->contentImage->setVisible(false);

        break;
    case ContentMode::Image:
        ui->contentText->setVisible(false);
        ui->contentImage->setVisible(true);
        break;
    case ContentMode::Table:

        break;
    }

}

PanelContent::ContentMode PanelContent::contentMode()
{
    return m_contentMode;
}
