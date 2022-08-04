#ifndef BLOCK_STROKE_ADVANCED_H
#define BLOCK_STROKE_ADVANCED_H

#include <QWidget>

namespace Ui {
class BlockStrokeAdvanced;
}

class BlockStrokeAdvanced : public QWidget
{
    Q_OBJECT

public:
    explicit BlockStrokeAdvanced(QWidget *parent = nullptr);
    ~BlockStrokeAdvanced();

private:
    Ui::BlockStrokeAdvanced *ui;

    void setup();
    void connectSlots();
};

#endif // BLOCK_STROKE_ADVANCED_H
