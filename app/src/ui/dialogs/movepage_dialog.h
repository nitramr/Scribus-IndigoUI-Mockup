#ifndef MOVEPAGE_DIALOG_H
#define MOVEPAGE_DIALOG_H

#include <QDialog>

namespace Ui {
class MovePageDialog;
}

class MovePageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MovePageDialog(QWidget *parent = nullptr);
    ~MovePageDialog();

private:
    Ui::MovePageDialog *ui;

    void setup();
};

#endif // MOVEPAGE_DIALOG_H
