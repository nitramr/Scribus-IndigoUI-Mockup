#ifndef TOOLBARQUICKTOOLS_H
#define TOOLBARQUICKTOOLS_H

#include "quicktool_document.h"
#include "quicktool_edit.h"
#include "quicktool_layer.h"
#include "quicktool_pdftools.h"
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
    QuickToolPDFTools * quickToolPDFTools;
    QuickToolEdit * quickToolEdit;
    QuickToolDocument * quickToolDocument;


    void loadWidgets();

};

#endif // TOOLBARQUICKTOOLS_H
