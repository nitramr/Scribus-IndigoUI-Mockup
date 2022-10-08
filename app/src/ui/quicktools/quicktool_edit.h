#ifndef QUICKTOOL_EDIT_H
#define QUICKTOOL_EDIT_H

#include "form_widget/form_widget.h"

namespace Ui {
class QuickToolEdit;
}

class QuickToolEdit : public FormWidget
{
    Q_OBJECT

public:
    explicit QuickToolEdit(QWidget *parent = nullptr);
    ~QuickToolEdit();

private:
    Ui::QuickToolEdit *ui;

    void setup();
};

#endif // QUICKTOOL_EDIT_H
