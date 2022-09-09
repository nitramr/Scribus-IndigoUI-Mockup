#ifndef NEWPARENTPAGE_DIALOG_H
#define NEWPARENTPAGE_DIALOG_H

#include "enums.h"
#include <QDialog>

namespace Ui {
class NewParentPageDialog;
}

class NewParentPageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewParentPageDialog(QWidget *parent = nullptr);
    ~NewParentPageDialog();

    void setPageLayout(PageLayout pageLayout);


private:
    Ui::NewParentPageDialog *ui;

    void setup();
};

#endif // NEWPARENTPAGE_DIALOG_H
