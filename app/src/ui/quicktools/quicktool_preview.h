#ifndef QUICKTOOL_QUICKTOOL_PREVIEW_H
#define QUICKTOOL_QUICKTOOL_PREVIEW_H


#include "form_widget/form_widget.h"

namespace Ui {
class QuickToolPreview;
}

class QuickToolPreview : public FormWidget
{
    Q_OBJECT

public:
    explicit QuickToolPreview(QWidget *parent = nullptr);
    ~QuickToolPreview();

private:
    Ui::QuickToolPreview *ui;

    void setup();
};

#endif // QUICKTOOL_PREVIEW_H
