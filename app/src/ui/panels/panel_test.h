#ifndef PANEL_TEST_H
#define PANEL_TEST_H

#include <QWidget>

namespace Ui {
class PanelTest;
}

class PanelTest : public QWidget
{
    Q_OBJECT

public:
    explicit PanelTest(QWidget *parent = nullptr);
    ~PanelTest();

private:
    Ui::PanelTest *ui;

    void setup();
};

#endif // PANEL_TEST_H
