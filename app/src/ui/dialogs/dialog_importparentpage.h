#ifndef DIALOG_IMPORTPARENTPAGE_H
#define DIALOG_IMPORTPARENTPAGE_H

#include <QDialog>

namespace Ui {
class DialogImportParentPage;
}

class DialogImportParentPage : public QDialog
{
    Q_OBJECT

public:
    explicit DialogImportParentPage(QWidget *parent = nullptr);
    ~DialogImportParentPage();

private:
    Ui::DialogImportParentPage *ui;

    void setup();
    void connectSlots();
};

#endif // DIALOG_IMPORTPARENTPAGE_H
