#ifndef COLORSWATCHES_H
#define COLORSWATCHES_H

#include "dialog_colorswatchimport.h"
#include "sccolor.h"
#include <QWidget>

namespace Ui {
class ColorSwatches;
}

class ColorSwatches : public QWidget
{
    Q_OBJECT

public:
    explicit ColorSwatches(QWidget *parent = nullptr);
    ~ColorSwatches();

    void setConfiguration(ItemFillMode mode);
    ItemFillMode configuration();

private:
    Ui::ColorSwatches *ui;
    DialogColorSwatchImport *dialogColorSwatchImport;
    ItemFillMode m_configuration {ItemFillMode::Solid};

    void setup();
    void connectSlots();

    void dummyContent();

private slots:
    void changedColor();
    void showColorSwatchImportDialog();

signals:
    void colorChanged(ScColor);

};

#endif // COLORSWATCHES_H
