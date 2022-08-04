#ifndef BLOCK_PARAGRAPH_ADVANCED_H
#define BLOCK_PARAGRAPH_ADVANCED_H

#include <QWidget>

namespace Ui {
class BlockParagraphAdvanced;
}

class BlockParagraphAdvanced : public QWidget
{
    Q_OBJECT

public:
    explicit BlockParagraphAdvanced(QWidget *parent = nullptr);
    ~BlockParagraphAdvanced();

private:
    Ui::BlockParagraphAdvanced *ui;
};

#endif // BLOCK_PARAGRAPH_ADVANCED_H
