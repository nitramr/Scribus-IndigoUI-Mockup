#include <QtDesigner/QExtensionFactory>
#include <QtDesigner/QExtensionManager>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QDesignerFormWindowInterface>
#include <QtDesigner/QDesignerContainerExtension>
#include <QtDesigner/QDesignerPropertySheetExtension>

#include <QIcon>
#include <QtPlugin>

#include "basepointwidget.h"
#include "basepointwidgetplugin.h"


BasePointWidgetPlugin::BasePointWidgetPlugin(QObject *parent)
    : QObject(parent)
{
}

QString BasePointWidgetPlugin::name() const
{
    return QLatin1String("BasePointWidget");
}

QString BasePointWidgetPlugin::group() const
{
    return QLatin1String("Indigo UI");
}

QString BasePointWidgetPlugin::toolTip() const
{
    return QString();
}

QString BasePointWidgetPlugin::whatsThis() const
{
    return QString();
}

QString BasePointWidgetPlugin::includeFile() const
{
    return QLatin1String("basepointwidget.h");
}

QIcon BasePointWidgetPlugin::icon() const
{
    return QIcon();
}

bool BasePointWidgetPlugin::isContainer() const
{
    return false;
}

QWidget *BasePointWidgetPlugin::createWidget(QWidget *parent)
{
    BasePointWidget *widget = new BasePointWidget(parent);
    return widget;

}

bool BasePointWidgetPlugin::isInitialized() const
{
    return initialized;
}

void BasePointWidgetPlugin::initialize(QDesignerFormEditorInterface *formEditor)
{
    Q_UNUSED(formEditor)
    if (initialized)
        return;

    initialized = true;
}

QString BasePointWidgetPlugin::domXml() const
{
    return QLatin1String(R"(
<ui language="c++" displayname="Base Point">
    <widget class="BasePointWidget" name="basePointWidget">
    </widget>
    <customwidgets>
        <customwidget>
            <class>BasePointWidget</class>
            <extends>QWidget</extends>
        </customwidget>
    </customwidgets>
</ui>)");
}
