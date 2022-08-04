#ifndef PANEL_OUTLINER_H
#define PANEL_OUTLINER_H

#include <QWidget>

namespace Ui {
class PanelOutliner;
}

class PanelOutliner : public QWidget
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
