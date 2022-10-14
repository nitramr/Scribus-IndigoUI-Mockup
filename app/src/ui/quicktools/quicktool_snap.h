#ifndef QUICKTOOL_SNAP_H
#define QUICKTOOL_SNAP_H

#include "form_widget/form_widget.h"

namespace Ui {
class QuickToolSnap;
}

class QuickToolSnap : public FormWidget
{
    Q_OBJECT

public:
    explicit QuickToolSnap(QWidget *parent = nullptr);
    ~QuickToolSnap();

private:
    Ui::QuickToolSnap *ui;

    void setup();
};

#endif // QUICKTOOL_SNAP_H
