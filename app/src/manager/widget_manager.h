#ifndef WIDGETMANAGER_H
#define WIDGETMANAGER_H

#include "stickypopup_widget/stickypopup.h"
#include <QObject>

class WidgetManager: public QObject
{

    Q_OBJECT
public:
    WidgetManager(WidgetManager const&) = delete;
    void operator=(WidgetManager const&) = delete;
    static WidgetManager &instance();

    void setup();

    StickyPopup * colorPicker();
    StickyPopup * colorPickerColor();

private:
    WidgetManager(QObject *parent = nullptr);
    ~WidgetManager() = default;

    static WidgetManager* m_instance;

    // Widgets
    StickyPopup * m_colorPicker;
    StickyPopup * m_colorPickerColor;

};

#endif // WIDGETMANAGER_H
