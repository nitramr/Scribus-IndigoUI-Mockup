#ifndef IMPORTPARENTPAGE_DIALOG_H
#define IMPORTPARENTPAGE_DIALOG_H

#include <QDialog>

namespace Ui {
class ImportParentPageDialog;
}

class ImportParentPageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportParentPageDialog(QWidget *parent = nullptr);
    ~ImportParentPageDialog();

private:
    Ui::ImportParentPageDialog *ui;

    void setup();
    void connectSlots();
};

#endif // IMPORTPARENTPAGE_DIALOG_H
