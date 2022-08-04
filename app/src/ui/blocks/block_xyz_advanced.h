#ifndef BLOCK_XYZ_ADVANCED_H
#define BLOCK_XYZ_ADVANCED_H

#include <QWidget>

namespace Ui {
class BlockXYZAdvanced;
}

class BlockXYZAdvanced : public QWidget
{
    Q_OBJECT

public:
    explicit BlockXYZAdvanced(QWidget *parent = nullptr);
    ~BlockXYZAdvanced();

private:
    Ui::BlockXYZAdvanced *ui;

    void connectSlots();

signals:
    void exportObject(bool state);
    void changedName(QString name);
};

#endif // BLOCK_XYZ_ADVANCED_H
