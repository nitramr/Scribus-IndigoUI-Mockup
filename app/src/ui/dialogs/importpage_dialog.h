#ifndef IMPORTPAGE_DIALOG_H
#define IMPORTPAGE_DIALOG_H

#include <QDialog>

namespace Ui {
class ImportPageDialog;
}

class ImportPageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportPageDialog(QWidget *parent = nullptr);
    ~ImportPageDialog();

private slots:
    void enableInsertPage(bool isEnabled);

private:
    Ui::ImportPageDialog *ui;

    void setup();
    void connectSlots();
};

#endif // IMPORTPAGE_DIALOG_H
