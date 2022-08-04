#ifndef DIALOG_NEWPARENTPAGE_H
#define DIALOG_NEWPARENTPAGE_H

#include "enums.h"
#include <QDialog>

namespace Ui {
class DialogNewParentPage;
}

class DialogNewParentPage : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewParentPage(QWidget *parent = nullptr);
    ~DialogNewParentPage();

    void setPageLayout(PageLayout pageLayout);


private:
    Ui::DialogNewParentPage *ui;

    void setup();
};

#endif // DIALOG_NEWPARENTPAGE_H
