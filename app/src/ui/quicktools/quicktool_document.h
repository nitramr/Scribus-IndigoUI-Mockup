#ifndef QUICKTOOL_DOCUMENT_H
#define QUICKTOOL_DOCUMENT_H

#include "form_widget/form_widget.h"

namespace Ui {
class QuickToolDocument;
}

class QuickToolDocument : public FormWidget
{
    Q_OBJECT

public:
    explicit QuickToolDocument(QWidget *parent = nullptr);
    ~QuickToolDocument();

private:
    Ui::QuickToolDocument *ui;

    void setup();
};

#endif // QUICKTOOL_DOCUMENT_H
