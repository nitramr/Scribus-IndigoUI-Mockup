#include "sectioncontainerextension.h"
#include "sectioncontainer.h"

SectionContainerExtension::SectionContainerExtension(SectionContainer *widget,
                                                                     QObject *parent)
    : QObject(parent)
    , myWidget(widget)
{
}

bool SectionContainerExtension::canAddWidget() const
{
    return true;
}

void SectionContainerExtension::addWidget(QWidget *widget)
{
    myWidget->addPage(widget);
}

int SectionContainerExtension::count() const
{
    return myWidget->count();
}

int SectionContainerExtension::currentIndex() const
{
    return myWidget->currentIndex();
}

void SectionContainerExtension::insertWidget(int index, QWidget *widget)
{
    myWidget->insertPage(index, widget);
}

bool SectionContainerExtension::canRemove(int index) const
{
    Q_UNUSED(index);
    return true;
}

void SectionContainerExtension::remove(int index)
{
    myWidget->removePage(index);
}

void SectionContainerExtension::setCurrentIndex(int index)
{
    myWidget->setCurrentIndex(index);
}

QWidget* SectionContainerExtension::widget(int index) const
{
    return myWidget->widget(index);
}
