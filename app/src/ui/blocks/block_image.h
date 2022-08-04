#ifndef BLOCK_IMAGE_H
#define BLOCK_IMAGE_H

#include <QWidget>

namespace Ui {
class BlockImage;
}

class BlockImage : public QWidget
{
    Q_OBJECT

public:
    explicit BlockImage(QWidget *parent = nullptr);
    ~BlockImage();

private:
    Ui::BlockImage *ui;

    void setup();
    void connectSlots();

private slots:
    void linkInput(bool state);
    void changeAutoFit(bool doesFit);

signals:
    void signalLinkInput(bool state);

};

#endif // BLOCK_IMAGE_H
