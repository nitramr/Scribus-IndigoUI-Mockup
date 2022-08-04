#ifndef DIALOG_IMPORTPAGE_H
#define DIALOG_IMPORTPAGE_H

#include <QDialog>

namespace Ui {
class DialogImportPage;
}

class DialogImportPage : public QDialog
{
    Q_OBJECT

public:
    explicit DialogImportPage(QWidget *parent = nullptr);
    ~DialogImportPage();

private slots:
    void enableInsertPage(bool isEnabled);

private:
    Ui::DialogImportPage *ui;

    void setup();
    void connectSlots();
};

#endif // DIALOG_IMPORTPAGE_H
