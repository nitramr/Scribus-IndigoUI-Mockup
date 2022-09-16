#ifndef PANEL_CONTENT_IMAGE_H
#define PANEL_CONTENT_IMAGE_H

#include "block_image.h"
#include "block_imageeffects.h"
#include "section_container/section_container.h"
#include "panel.h"
#include <QWidget>

namespace Ui {
class PanelContentImage;
}

class PanelContentImage : public Panel
{
    Q_OBJECT

public:
    explicit PanelContentImage(QWidget *parent = nullptr);
    ~PanelContentImage();

private:
    Ui::PanelContentImage *ui;

    BlockImage * blockImage;
    BlockImageEffects * blockImageEffects;

    void setup();
    void connectSlots();

private slots:
    void updateLayout(bool isCollapsed);
};

#endif // PANEL_CONTENT_IMAGE_H
