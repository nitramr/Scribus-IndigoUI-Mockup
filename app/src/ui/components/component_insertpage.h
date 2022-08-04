#ifndef COMPONENT_INSERTPAGE_H
#define COMPONENT_INSERTPAGE_H

#include <QWidget>
#include <QSpinBox>
#include <QComboBox>

namespace Ui {
class ComponentInsertPage;
}

class ComponentInsertPage : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentInsertPage(QWidget *parent = nullptr);
    ~ComponentInsertPage();

    QComboBox * comboInsertType();
    QSpinBox * numberPage();

private slots:
    void enablePageInput();

private:
    Ui::ComponentInsertPage *ui;

    void setup();
    void connectSlots();
};

#endif // COMPONENT_INSERTPAGE_H
