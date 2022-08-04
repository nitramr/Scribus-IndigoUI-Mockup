#ifndef DIALOG_MANAGEPAGEPROPERTIES_H
#define DIALOG_MANAGEPAGEPROPERTIES_H

#include <QDialog>

namespace Ui {
class DialogManagePageProperties;
}

class DialogManagePageProperties : public QDialog
{
    Q_OBJECT

public:
    explicit DialogManagePageProperties(QWidget *parent = nullptr);
    ~DialogManagePageProperties();

private:
    Ui::DialogManagePageProperties *ui;

    void setup();
};

#endif // DIALOG_MANAGEPAGEPROPERTIES_H
