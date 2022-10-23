#ifndef STYLEMANAGER_DIALOG_H
#define STYLEMANAGER_DIALOG_H

#include <QDialog>

class QTreeWidgetItem;

namespace Ui {
class StyleManagerDialog;
}

class StyleManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StyleManagerDialog(QWidget *parent = nullptr);
    ~StyleManagerDialog();

private:
    Ui::StyleManagerDialog *ui;

    void setup();
    void connectSlots();

private slots:

    void changeStyleSelection(QTreeWidgetItem *item);

};

#endif // STYLEMANAGER_DIALOG_H
