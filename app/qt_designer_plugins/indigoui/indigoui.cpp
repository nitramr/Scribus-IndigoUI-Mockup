#include "indigoui.h"


IndigoUI::IndigoUI(QObject *parent)
        : QObject(parent)
{
    widgets.append(new BasePointWidgetPlugin(this));
    widgets.append(new FormWidgetPlugin(this));
    widgets.append(new SectionContainerPlugin(this));
}

QList<QDesignerCustomWidgetInterface*> IndigoUI::customWidgets() const
{
    return widgets;
}
