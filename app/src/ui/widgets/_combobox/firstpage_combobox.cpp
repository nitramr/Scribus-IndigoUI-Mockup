#include "firstpage_combobox.h"

FirstPageComboBox::FirstPageComboBox(QWidget *parent) : QComboBox(parent)
{

}

void FirstPageComboBox::setPageLayout(PageLayout pageLayout)
{
    m_pageLayout = pageLayout;

    this->clear();

    switch(m_pageLayout){
    case PageLayout::Single:
        break;
    case PageLayout::Double:
        this->addItem("Left", QVariant::fromValue(FirstPage::Left));
        this->addItem("Right", QVariant::fromValue(FirstPage::Right));
        this->setCurrentIndex(1);
        break;
    case PageLayout::ThreeFacing:
        this->addItem("Left", QVariant::fromValue(FirstPage::Left));
        this->addItem("Middle", QVariant::fromValue(FirstPage::Middle));
        this->addItem("Right", QVariant::fromValue(FirstPage::Right));
        break;
    case PageLayout::FourFacing:
        this->addItem("Left", QVariant::fromValue(FirstPage::Left));
        this->addItem("Middle Left", QVariant::fromValue(FirstPage::MiddleLeft));
        this->addItem("Middle Right", QVariant::fromValue(FirstPage::MiddleRight));
        this->addItem("Right", QVariant::fromValue(FirstPage::Right));
        break;
    }
}

PageLayout FirstPageComboBox::pageLayout()
{
    return m_pageLayout;
}
