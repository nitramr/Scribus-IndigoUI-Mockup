#ifndef TOOLBARQUICKTOOLS_H
#define TOOLBARQUICKTOOLS_H

#include "quicktool_layer.h"
#include "quicktool_preview.h"
#include "toolbarproperty.h"
#include <QWidget>

class ToolBarQuickTools : public ToolBarProperty
{
public:
    ToolBarQuickTools(QWidget *parent = nullptr);

private:

    // Widgets
    QuickToolPreview * quickToolPreview;
    QuickToolLayer * quickToolLayer;


    void loadWidgets();

};

#endif // TOOLBARQUICKTOOLS_H
