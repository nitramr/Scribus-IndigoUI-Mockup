#ifndef COMPONENT_SPACEINPUT_H
#define COMPONENT_SPACEINPUT_H

#include "advancedspinbox.h"
#include "formwidget.h"
#include <QToolButton>
#include <QWidget>

namespace Ui {
class ComponentSpaceInput;
}

class ComponentSpaceInput : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentSpaceInput(QWidget *parent = nullptr);
    ~ComponentSpaceInput();

    FormWidget * layoutLeft();
    FormWidget * layoutBottom();
    FormWidget * layoutRight();
    FormWidget * layoutTop();
    AdvancedSpinBox * numberLeft();
    AdvancedSpinBox * numberBottom();
    AdvancedSpinBox * numberRight();
    AdvancedSpinBox * numberTop();
    QToolButton * buttonLink();



private slots:
    void linkInput(bool state);

private:
    Ui::ComponentSpaceInput *ui;

    void setup();
    void connectSlots();

signals:
    void signalLinkInput(bool);
};

#endif // COMPONENT_SPACEINPUT_H
