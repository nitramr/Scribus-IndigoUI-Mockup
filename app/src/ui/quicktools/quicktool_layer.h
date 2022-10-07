#ifndef QUICKTOOL_LAYER_H
#define QUICKTOOL_LAYER_H

#include "form_widget/form_widget.h"

namespace Ui {
class QuickToolLayer;
}

class QuickToolLayer : public FormWidget
{
    Q_OBJECT

public:
    explicit QuickToolLayer(QWidget *parent = nullptr);
    ~QuickToolLayer();

private:
    Ui::QuickToolLayer *ui;

    void setup();
};

#endif // QUICKTOOL_LAYER_H
