#ifndef DIALOG_NEWPAGE_H
#define DIALOG_NEWPAGE_H

#include "enums.h"
#include <QDialog>

namespace Ui {
class DialogNewPage;
}

class DialogNewPage : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewPage(QWidget *parent = nullptr);
    ~DialogNewPage();

    void setPageLayout(PageLayout pageLayout);

private:
    Ui::DialogNewPage *ui;

    void setup();
};

#endif // DIALOG_NEWPAGE_H
