#ifndef TOOLBARQUICKTOOLS_H
#define TOOLBARQUICKTOOLS_H

#include "quicktool_document.h"
#include "quicktool_edit.h"
#include "quicktool_level.h"
#include "quicktool_pdftools.h"
#include "quicktool_preview.h"
#include "quicktool_snap.h"
#include "toolbarproperty.h"
#include <QWidget>

class ToolBarQuickTools : public ToolBarProperty
{
public:
    ToolBarQuickTools(QWidget *parent = nullptr);

private:

    // Widgets
    QuickToolPreview * quickToolPreview;
    QuickToolLevel * quickToolLevel;
    QuickToolPDFTools * quickToolPDFTools;
    QuickToolEdit * quickToolEdit;
    QuickToolDocument * quickToolDocument;
    QuickToolSnap * quickToolSnap;


    void loadWidgets();

};

#endif // TOOLBARQUICKTOOLS_H
