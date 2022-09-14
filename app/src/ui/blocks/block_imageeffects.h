#ifndef BLOCK_IMAGEEFFECTS_H
#define BLOCK_IMAGEEFFECTS_H

#include <QWidget>

namespace Ui {
class BlockImageEffects;
}

class BlockImageEffects : public QWidget
{
    Q_OBJECT

public:
    explicit BlockImageEffects(QWidget *parent = nullptr);
    ~BlockImageEffects();

private:
    Ui::BlockImageEffects *ui;

    void setup();
};

#endif // BLOCK_IMAGEEFFECTS_H
