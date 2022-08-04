#ifndef INDIGOUI_H
#define INDIGOUI_H

#include <QtCore/qplugin.h>
#include <QtUiPlugin/QDesignerCustomWidgetCollectionInterface>

#include "formwidgetplugin.h"
#include "basepointwidgetplugin.h"
#include "sectioncontainerplugin.h"

class IndigoUI: public QObject, public QDesignerCustomWidgetCollectionInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "net.scribus.indigo.WidgetLibrary")
    Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

public:
    IndigoUI(QObject *parent = 0);

    QList<QDesignerCustomWidgetInterface*> customWidgets() const override;

private:
    QList<QDesignerCustomWidgetInterface*> widgets;
};


#endif // INDIGOUI_H
