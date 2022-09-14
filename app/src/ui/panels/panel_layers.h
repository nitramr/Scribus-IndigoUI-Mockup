#ifndef PANEL_LAYERS_H
#define PANEL_LAYERS_H

#include <QWidget>
#include "sclayers.h"
#include "panel.h"

namespace Ui {
class PanelLayers;
}

class PanelLayers : public Panel
{
    Q_OBJECT

public:
    explicit PanelLayers(QWidget *parent = nullptr);
    ~PanelLayers();

private:
    Ui::PanelLayers *ui;

    void setup();
    void rebuildList();

protected:
    ScLayers *layers { nullptr };
};

#endif // PANEL_LAYERS_H
