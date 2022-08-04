#ifndef BLOCK_CHARACTER_H
#define BLOCK_CHARACTER_H

#include <QWidget>

namespace Ui {
class BlockCharacter;
}

class BlockCharacter : public QWidget
{
    Q_OBJECT

public:
    explicit BlockCharacter(QWidget *parent = nullptr);
    ~BlockCharacter();

private:
    Ui::BlockCharacter *ui;

    void setup();
};

#endif // BLOCK_CHARACTER_H
