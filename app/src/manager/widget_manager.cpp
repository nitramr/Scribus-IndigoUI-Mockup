#include "widget_manager.h"
#include <QDebug>

#include "colorpicker.h"

WidgetManager* WidgetManager::m_instance = nullptr;

WidgetManager::WidgetManager(QObject *parent)
    : QObject(parent)
{
   // setup();

}

WidgetManager &WidgetManager::instance()
{
    static WidgetManager m_instance;
    return m_instance;
}

void WidgetManager::setup()
{

    m_colorPicker = new StickyPopup(new ColorPicker(ColorPickerConfig::Default));
    m_colorPickerColor = new StickyPopup(new ColorPicker(ColorPickerConfig::Text));

}


StickyPopup *WidgetManager::colorPicker()
{
    return m_colorPicker;
}

StickyPopup *WidgetManager::colorPickerColor()
{
    return m_colorPickerColor;
}
