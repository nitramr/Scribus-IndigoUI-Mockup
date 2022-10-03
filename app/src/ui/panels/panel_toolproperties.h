#ifndef PANEL_TOOLPROPERTIES_H
#define PANEL_TOOLPROPERTIES_H

#include <QWidget>
#include "panel.h"

namespace Ui {
class PanelToolProperties;
}

class PanelToolProperties : public Panel
{
    Q_OBJECT

public:
    explicit PanelToolProperties(QWidget *parent = nullptr);
    ~PanelToolProperties();

private:
    Ui::PanelToolProperties *ui;

    void setup();
};

#endif // PANEL_TOOLPROPERTIES_H
