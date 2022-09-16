#include <QtDesigner/QExtensionFactory>
#include <QtDesigner/QExtensionManager>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QDesignerFormWindowInterface>
#include <QtDesigner/QDesignerContainerExtension>
#include <QtDesigner/QDesignerPropertySheetExtension>

#include <QIcon>
#include <QtPlugin>

#include "headline_widget/headline_widget.h"
#include "headlinewidgetplugin.h"


HeadlineWidgetPlugin::HeadlineWidgetPlugin(QObject *parent)
    : QObject(parent)
{
}

QString HeadlineWidgetPlugin::name() const
{
    return QLatin1String("HeadlineWidget");
}

QString HeadlineWidgetPlugin::group() const
{
    return QLatin1String("Indigo UI");
}

QString HeadlineWidgetPlugin::toolTip() const
{
    return QString();
}

QString HeadlineWidgetPlugin::whatsThis() const
{
    return QString();
}

QString HeadlineWidgetPlugin::includeFile() const
{
    return QLatin1String("headline_widget/headline_widget.h");
}

QIcon HeadlineWidgetPlugin::icon() const
{
    return QIcon();
}

bool HeadlineWidgetPlugin::isContainer() const
{
    return true;
}

QWidget *HeadlineWidgetPlugin::createWidget(QWidget *parent)
{
    HeadlineWidget *widget = new HeadlineWidget(parent);
    return widget;
}

bool HeadlineWidgetPlugin::isInitialized() const
{
    return initialized;
}

void HeadlineWidgetPlugin::initialize(QDesignerFormEditorInterface *formEditor)
{
    Q_UNUSED(formEditor)
    if (initialized)
        return;

    initialized = true;
}

QString HeadlineWidgetPlugin::domXml() const
{
    return QLatin1String(R"(
<ui language="c++" displayname="Headline Widget">
    <widget class="HeadlineWidget" name="headlineWidget">
     <property name="text">
      <string>Headline</string>
     </property>
    </widget>
    <customwidgets>
        <customwidget>
            <class>HeadlineWidget</class>
            <extends>QWidget</extends>
        </customwidget>
    </customwidgets>
</ui>)");
}
