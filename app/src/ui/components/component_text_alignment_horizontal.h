#ifndef COMPONENT_TEXT_ALIGNMENT_HORIZONTAL_H
#define COMPONENT_TEXT_ALIGNMENT_HORIZONTAL_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class ComponentTextAlignmentHorizontal;
}

class ComponentTextAlignmentHorizontal : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentTextAlignmentHorizontal(QWidget *parent = nullptr);
    ~ComponentTextAlignmentHorizontal();

private:
    Ui::ComponentTextAlignmentHorizontal *ui;

    QButtonGroup *direction;

    void setup();
    void connectSlots();

private slots:
    void changedTextDirection(int id, bool checked);
};

#endif // COMPONENT_TEXT_ALIGNMENT_HORIZONTAL_H
