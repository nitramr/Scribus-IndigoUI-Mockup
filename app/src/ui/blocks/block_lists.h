#ifndef BLOCK_LISTS_H
#define BLOCK_LISTS_H

#include "enums.h"
#include <QWidget>

namespace Ui {
class BlockLists;
}

class BlockLists : public QWidget
{
    Q_OBJECT

public:
    explicit BlockLists(QWidget *parent = nullptr);
    ~BlockLists();

private:
    Ui::BlockLists *ui;

    void setup();
    void connectSlots();

    ListType m_listType {ListType::None};

private slots:
    void changeListType();

};

#endif // BLOCK_LISTS_H
