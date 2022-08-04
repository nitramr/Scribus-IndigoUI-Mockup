#ifndef PANEL_ALIGNDISTRIBUTE_H
#define PANEL_ALIGNDISTRIBUTE_H

#include "block_alignment.h"
#include "block_distribution.h"
#include <QWidget>

namespace Ui {
class PanelAlignDistribute;
}

class PanelAlignDistribute : public QWidget
{
    Q_OBJECT

public:
    explicit PanelAlignDistribute(QWidget *parent = nullptr);
    ~PanelAlignDistribute();

private:
    Ui::PanelAlignDistribute *ui;

    BlockAlignment *     blockAlignment;
    BlockDistribution *  blockDistribution;

    void setup();
};

#endif // PANEL_ALIGNDISTRIBUTE_H
