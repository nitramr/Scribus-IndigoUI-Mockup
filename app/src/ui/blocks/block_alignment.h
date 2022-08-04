#ifndef BLOCK_ALIGNMENT_H
#define BLOCK_ALIGNMENT_H

#include <QWidget>

namespace Ui {
class BlockAlignment;
}

class BlockAlignment : public QWidget
{
    Q_OBJECT

public:
    explicit BlockAlignment(QWidget *parent = nullptr);
    ~BlockAlignment();

private:
    Ui::BlockAlignment *ui;

    void setup();
    void connectSlots();

private slots:

    void changeReference();
};

#endif // BLOCK_ALIGNMENT_H
