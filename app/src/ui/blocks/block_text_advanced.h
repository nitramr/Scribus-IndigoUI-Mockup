#ifndef BLOCK_TEXT_ADVANCED_H
#define BLOCK_TEXT_ADVANCED_H

#include <QWidget>


namespace Ui {
class BlockTextAdvanced;
}

class BlockTextAdvanced : public QWidget
{
    Q_OBJECT

public:
    explicit BlockTextAdvanced(QWidget *parent = nullptr);
    ~BlockTextAdvanced();

private:
    Ui::BlockTextAdvanced *ui;

    void setup();
};

#endif // BLOCK_TEXT_ADVANCED_H
