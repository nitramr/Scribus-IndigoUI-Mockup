#ifndef DUPLICATEPAGE_DIALOG_H
#define DUPLICATEPAGE_DIALOG_H

#include <QDialog>

namespace Ui {
class DuplicatePageDialog;
}

class DuplicatePageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DuplicatePageDialog(QWidget *parent = nullptr);
    ~DuplicatePageDialog();

private:
    Ui::DuplicatePageDialog *ui;

    void setup();
};

#endif // DUPLICATEPAGE_DIALOG_H
