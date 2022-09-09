#ifndef NEWDOCUMENT_DIALOG_H
#define NEWDOCUMENT_DIALOG_H

#include <QButtonGroup>
#include <QDialog>

namespace Ui {
class NewDocumentDialog;
}

class NewDocumentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewDocumentDialog(QWidget *parent = nullptr);
    ~NewDocumentDialog();

private:
    Ui::NewDocumentDialog *ui;

    QButtonGroup *orientationButtons;

    void setup();
    void connectSlots();

    void dummyContent();

private slots:

//    void linkBleed(bool state);
//    void linkMargin(bool state);
    void changedPageLayout();

    void accept();
};

#endif // NEWDOCUMENT_DIALOG_H
