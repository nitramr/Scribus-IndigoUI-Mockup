#ifndef BLOCK_XYZ_TRANSFORMATION_H
#define BLOCK_XYZ_TRANSFORMATION_H

#include <QWidget>

namespace Ui {
class BlockXYZTransformation;
}

class BlockXYZTransformation : public QWidget
{
    Q_OBJECT

public:
    explicit BlockXYZTransformation(QWidget *parent = nullptr);
    ~BlockXYZTransformation();

public slots:
    void flipVertical(bool state);
    void flipHorizontal(bool state);
    void lockFrame(bool state);

private:
    Ui::BlockXYZTransformation *ui;

    void connectSlots();

signals:
    void signalRotate(double angle);
};

#endif // BLOCK_XYZ_TRANSFORMATION_H
