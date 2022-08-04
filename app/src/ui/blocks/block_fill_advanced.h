#ifndef BLOCK_FILL_ADVANCED_H
#define BLOCK_FILL_ADVANCED_H

#include <QWidget>

namespace Ui {
class BlockFillAdvanced;
}

class BlockFillAdvanced : public QWidget
{
    Q_OBJECT

public:
    explicit BlockFillAdvanced(QWidget *parent = nullptr);
    ~BlockFillAdvanced();

private:
    Ui::BlockFillAdvanced *ui;

    void setup();
    void connectSlots();
};

#endif // BLOCK_FILL_ADVANCED_H
