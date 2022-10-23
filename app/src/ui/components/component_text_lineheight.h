#ifndef COMPONENT_TEXT_LINEHEIGHT_H
#define COMPONENT_TEXT_LINEHEIGHT_H

#include <QWidget>

namespace Ui {
class ComponentTextLineHeight;
}

class ComponentTextLineHeight : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentTextLineHeight(QWidget *parent = nullptr);
    ~ComponentTextLineHeight();

private:
    Ui::ComponentTextLineHeight *ui;

    void setup();
    void connectSlots();

private slots:
    void changedLineSpacing();
};

#endif // COMPONENT_TEXT_LINEHEIGHT_H
