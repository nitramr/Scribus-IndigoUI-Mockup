#ifndef HEADLINEWIDGETPLUGIN_H
#define HEADLINEWIDGETPLUGIN_H

#include <QtUiPlugin/QDesignerCustomWidgetInterface>

QT_BEGIN_NAMESPACE
class QIcon;
class QWidget;
QT_END_NAMESPACE

class HeadlineWidgetPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
//    Q_PLUGIN_METADATA(IID "net.scribus.indigo.HeadlineWidget")
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    explicit HeadlineWidgetPlugin(QObject *parent = nullptr);

    QString name() const override;
    QString group() const override;
    QString toolTip() const override;
    QString whatsThis() const override;
    QString includeFile() const override;
    QIcon icon() const override;
    bool isContainer() const override;
    QWidget *createWidget(QWidget *parent) override;
    bool isInitialized() const override;
    void initialize(QDesignerFormEditorInterface *formEditor) override;
    QString domXml() const override;

private:
    bool initialized = false;
};


#endif // HEADLINEWIDGETPLUGIN_H