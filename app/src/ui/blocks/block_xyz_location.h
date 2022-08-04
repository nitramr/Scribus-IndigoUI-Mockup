#ifndef BLOCK_XYZ_LOCATION_H
#define BLOCK_XYZ_LOCATION_H

#include <QWidget>

namespace Ui {
class BlockXYZLocation;
}

class BlockXYZLocation : public QWidget
{
    Q_OBJECT

public:
    explicit BlockXYZLocation(QWidget *parent = nullptr);
    ~BlockXYZLocation();

public slots:
    void lockFrame(bool state);
    void lockSize(bool state);
    void linkSize(bool state);
    void rotate(double angle);

private:
    Ui::BlockXYZLocation *ui;

    void setup();
    void connectSlots();

signals:

    void signalLockFrame(bool);
    void signalLockSize(bool);
    void signalLinkSize(bool);

};

#endif // BLOCK_XYZ_LOCATION_H
