#ifndef QUICKTOOL_LEVEL_H
#define QUICKTOOL_LEVEL_H

#include "form_widget/form_widget.h"

namespace Ui {
class QuickToolLevel;
}

class QuickToolLevel : public FormWidget
{
    Q_OBJECT

public:
    explicit QuickToolLevel(QWidget *parent = nullptr);
    ~QuickToolLevel();

private:
    Ui::QuickToolLevel *ui;

    void setup();
};

#endif // QUICKTOOL_LEVEL_H
