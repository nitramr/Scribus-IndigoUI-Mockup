#ifndef DIALOG_COLORSWATCHIMPORT_H
#define DIALOG_COLORSWATCHIMPORT_H

#include <QDialog>

namespace Ui {
class DialogColorSwatchImport;
}

class DialogColorSwatchImport : public QDialog
{
    Q_OBJECT

public:
    explicit DialogColorSwatchImport(QWidget *parent = nullptr);
    ~DialogColorSwatchImport();

private:
    Ui::DialogColorSwatchImport *ui;

    void setup();
};

#endif // DIALOG_COLORSWATCHIMPORT_H
