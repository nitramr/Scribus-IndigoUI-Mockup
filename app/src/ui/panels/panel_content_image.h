#ifndef PANEL_CONTENT_IMAGE_H
#define PANEL_CONTENT_IMAGE_H

#include "block_image.h"
#include "sectioncontainer.h"
#include <QWidget>

namespace Ui {
class PanelContentImage;
}

class PanelContentImage : public QWidget
{
    Q_OBJECT

public:
    explicit PanelContentImage(QWidget *parent = nullptr);
    ~PanelContentImage();

private:
    Ui::PanelContentImage *ui;

    BlockImage * blockImage;

    void setup();
    void addMenu(SectionContainer *section, QWidget *menuPanel);
};

#endif // PANEL_CONTENT_IMAGE_H
