#ifndef NEWPAGE_DIALOG_H
#define NEWPAGE_DIALOG_H

#include "enums.h"
#include <QDialog>

namespace Ui {
class NewPageDialog;
}

class NewPageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPageDialog(QWidget *parent = nullptr);
    ~NewPageDialog();

    void setPageLayout(PageLayout pageLayout);

private:
    Ui::NewPageDialog *ui;

    void setup();
};

#endif // NEWPAGE_DIALOG_H
