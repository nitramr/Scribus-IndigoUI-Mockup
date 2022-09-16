#ifndef COMPONENT_MARGINS_H
#define COMPONENT_MARGINS_H

#include "advanced_spinbox/advanced_spinbox.h"
#include "component_spaceinput.h"
#include "form_widget/form_widget.h"
#include <QPushButton>
#include <QComboBox>
#include <QWidget>

namespace Ui {
class ComponentMargins;
}

class ComponentMargins : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentMargins(QWidget *parent = nullptr);
    ~ComponentMargins();

    ComponentSpaceInput * componentSpaceInput();
    QComboBox * comboMarginPreset();
    QPushButton * buttonPrinterMargins();

private:
    Ui::ComponentMargins *ui;

    void setup();
};

#endif // COMPONENT_MARGINS_H
