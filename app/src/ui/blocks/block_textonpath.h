#ifndef BLOCK_TEXTONPATH_H
#define BLOCK_TEXTONPATH_H

#include <QWidget>

namespace Ui {
class BlockTextOnPath;
}

class BlockTextOnPath : public QWidget
{
    Q_OBJECT

public:
    explicit BlockTextOnPath(QWidget *parent = nullptr);
    ~BlockTextOnPath();

private:
    Ui::BlockTextOnPath *ui;

    void setup();
};

#endif // BLOCK_TEXTONPATH_H
