#ifndef BLOCK_DISTRIBUTION_H
#define BLOCK_DISTRIBUTION_H

#include <QWidget>

namespace Ui {
class BlockDistribution;
}

class BlockDistribution : public QWidget
{
    Q_OBJECT

public:
    explicit BlockDistribution(QWidget *parent = nullptr);
    ~BlockDistribution();

private:
    Ui::BlockDistribution *ui;

    void setup();
    void connectSlots();

};

#endif // BLOCK_DISTRIBUTION_H
