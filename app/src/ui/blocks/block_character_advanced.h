#ifndef BLOCK_CHARACTER_ADVANCED_H
#define BLOCK_CHARACTER_ADVANCED_H

#include <QWidget>

namespace Ui {
class BlockCharacterAdvanced;
}

class BlockCharacterAdvanced : public QWidget
{
    Q_OBJECT

public:
    explicit BlockCharacterAdvanced(QWidget *parent = nullptr);
    ~BlockCharacterAdvanced();

private:
    Ui::BlockCharacterAdvanced *ui;
};

#endif // BLOCK_CHARACTER_ADVANCED_H
