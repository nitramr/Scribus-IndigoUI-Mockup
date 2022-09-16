#include "sectioncontainerextensionfactory.h"
#include "sectioncontainerextension.h"
#include "section_container/section_container.h"


SectionContainerExtensionFactory::SectionContainerExtensionFactory(QExtensionManager *parent)
    : QExtensionFactory(parent)
{}

QObject *SectionContainerExtensionFactory::createExtension(QObject *object,
                                                          const QString &iid,
                                                          QObject *parent) const
{
    SectionContainer *widget = qobject_cast<SectionContainer*>(object);

    if (widget && (iid == Q_TYPEID(QDesignerContainerExtension)))
        return new SectionContainerExtension(widget, parent);
    return nullptr;
}
