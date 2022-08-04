#ifndef BLOCK_SHAPE_H
#define BLOCK_SHAPE_H

#include <QWidget>

namespace Ui {
class BlockShape;
}

class BlockShape : public QWidget
{
    Q_OBJECT

public:
    explicit BlockShape(QWidget *parent = nullptr);
    ~BlockShape();

public slots:
    void lockFrame(bool state);
    void lockSize(bool state);

private:
    Ui::BlockShape *ui;
    void connectSlots();
    bool m_lockSize;
    bool m_lockFrame;
};

#endif // BLOCK_SHAPE_H
