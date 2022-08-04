#ifndef DIALOG_NEWDOCUMENT_H
#define DIALOG_NEWDOCUMENT_H

#include <QButtonGroup>
#include <QDialog>

namespace Ui {
class DialogNewDocument;
}

class DialogNewDocument : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewDocument(QWidget *parent = nullptr);
    ~DialogNewDocument();

private:
    Ui::DialogNewDocument *ui;

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

#endif // DIALOG_NEWDOCUMENT_H
