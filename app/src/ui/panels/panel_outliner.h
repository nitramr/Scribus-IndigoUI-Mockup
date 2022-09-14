#ifndef PANEL_OUTLINER_H
#define PANEL_OUTLINER_H

#include <QWidget>
#include "panel.h"

namespace Ui {
class PanelOutliner;
}

class PanelOutliner : public Panel
{
    Q_OBJECT

public:
    explicit PanelOutliner(QWidget *parent = nullptr);
    ~PanelOutliner();

private:
    Ui::PanelOutliner *ui;

    void setup();
};

#endif // PANEL_OUTLINER_H
