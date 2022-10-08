#ifndef QUICKTOOL_PDFTOOLS_H
#define QUICKTOOL_PDFTOOLS_H

#include "form_widget/form_widget.h"

namespace Ui {
class QuickToolPDFTools;
}

class QuickToolPDFTools : public FormWidget
{
    Q_OBJECT

public:
    explicit QuickToolPDFTools(QWidget *parent = nullptr);
    ~QuickToolPDFTools();

private:
    Ui::QuickToolPDFTools *ui;

    void setup();
};

#endif // QUICKTOOL_PDFTOOLS_H
