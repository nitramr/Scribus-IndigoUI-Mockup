#ifndef STYLEMANAGER_DIALOG_H
#define STYLEMANAGER_DIALOG_H

#include <QDialog>

namespace Ui {
class StyleManagerDialog;
}

class StyleManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StyleManagerDialog(QWidget *parent = nullptr);
    ~StyleManagerDialog();

private:
    Ui::StyleManagerDialog *ui;
};

#endif // STYLEMANAGER_DIALOG_H
