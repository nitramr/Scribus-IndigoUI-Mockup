#ifndef COMPONENT_CURVEWIDGET_H
#define COMPONENT_CURVEWIDGET_H

#include <QWidget>

namespace Ui {
class ComponentCurveWidget;
}

class ComponentCurveWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentCurveWidget(QWidget *parent = nullptr);
    ~ComponentCurveWidget();

private:
    Ui::ComponentCurveWidget *ui;

    void setup();
    void connectSlots();

private slots:

    void toggleCurveBezier();
};

#endif // COMPONENT_CURVEWIDGET_H
