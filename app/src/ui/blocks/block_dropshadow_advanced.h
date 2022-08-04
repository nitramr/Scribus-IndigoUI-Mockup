#ifndef BLOCK_DROPSHADOW_ADVANCED_H
#define BLOCK_DROPSHADOW_ADVANCED_H

#include <QWidget>

namespace Ui {
class BlockDropShadowAdvanced;
}

class BlockDropShadowAdvanced : public QWidget
{
    Q_OBJECT

public:
    explicit BlockDropShadowAdvanced(QWidget *parent = nullptr);
    ~BlockDropShadowAdvanced();

private:
    Ui::BlockDropShadowAdvanced *ui;
};

#endif // BLOCK_DROPSHADOW_ADVANCED_H
