#ifndef COLORSWATCHIMPORT_DIALOG_H
#define COLORSWATCHIMPORT_DIALOG_H

#include <QDialog>

namespace Ui {
class ColorSwatchImportDialog;
}

class ColorSwatchImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorSwatchImportDialog(QWidget *parent = nullptr);
    ~ColorSwatchImportDialog();

private:
    Ui::ColorSwatchImportDialog *ui;

    void setup();
};

#endif // COLORSWATCHIMPORT_DIALOG_H
