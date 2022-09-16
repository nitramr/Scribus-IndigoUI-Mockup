#ifndef PANEL_FRAME_H
#define PANEL_FRAME_H

#include <QWidget>

#include "block_dropshadow.h"
#include "block_dropshadow_advanced.h"
#include "block_fill_advanced.h"
#include "block_stroke.h"
#include "block_stroke_advanced.h"
#include "block_xyz_location.h"
#include "block_xyz_advanced.h"
#include "block_shape.h"
#include "block_fill.h"
#include "panel.h"
#include "section_container/section_container.h"

namespace Ui {
class PanelFrame;
}

class PanelFrame : public Panel
{
    Q_OBJECT

public:
    explicit PanelFrame(QWidget *parent = nullptr);
    ~PanelFrame();

private:
    Ui::PanelFrame *ui;

    BlockXYZLocation *          blockXYZLocation;
     BlockXYZAdvanced *          blockXYZAdvanced;
    BlockShape *                blockShape;
    BlockFill *                 blockFill;
    BlockFillAdvanced *         blockFillAdvanced;
    BlockStroke *               blockStroke;
    BlockStrokeAdvanced *       blockStrokeAdvanced;
    BlockDropShadow *           blockDropShadow;
    BlockDropShadowAdvanced *   blockDropShadowAdvanced;

    void setup();
    void connectSlots();


};

#endif // PANEL_FRAME_H
