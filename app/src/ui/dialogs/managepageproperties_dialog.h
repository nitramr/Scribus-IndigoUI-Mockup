#ifndef MANAGEPAGEPROPERTIES_DIALOG_H
#define MANAGEPAGEPROPERTIES_DIALOG_H

#include <QDialog>

namespace Ui {
class ManagePagePropertiesDialog;
}

class ManagePagePropertiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManagePagePropertiesDialog(QWidget *parent = nullptr);
    ~ManagePagePropertiesDialog();

private:
    Ui::ManagePagePropertiesDialog *ui;

    void setup();
};

#endif // MANAGEPAGEPROPERTIES_DIALOG_H
