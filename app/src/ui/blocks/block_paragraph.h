#ifndef BLOCK_PARAGRAPH_H
#define BLOCK_PARAGRAPH_H

#include <QWidget>

namespace Ui {
class BlockParagraph;
}

class BlockParagraph : public QWidget
{
    Q_OBJECT

public:
    explicit BlockParagraph(QWidget *parent = nullptr);
    ~BlockParagraph();

public slots:
    void columnsChanged(int count);

private:
    Ui::BlockParagraph *ui;

    void setup();
    void connectSlots();

};

#endif // BLOCK_PARAGRAPH_H
