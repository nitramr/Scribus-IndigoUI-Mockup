#ifndef DIALOG_MOVEPAGE_H
#define DIALOG_MOVEPAGE_H

#include <QDialog>

namespace Ui {
class DialogMovePage;
}

class DialogMovePage : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMovePage(QWidget *parent = nullptr);
    ~DialogMovePage();

private:
    Ui::DialogMovePage *ui;

    void setup();
};

#endif // DIALOG_MOVEPAGE_H
