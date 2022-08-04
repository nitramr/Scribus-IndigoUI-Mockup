#ifndef DIALOG_DUPLICATEPAGE_H
#define DIALOG_DUPLICATEPAGE_H

#include <QDialog>

namespace Ui {
class DialogDuplicatePage;
}

class DialogDuplicatePage : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDuplicatePage(QWidget *parent = nullptr);
    ~DialogDuplicatePage();

private:
    Ui::DialogDuplicatePage *ui;

    void setup();
};

#endif // DIALOG_DUPLICATEPAGE_H
