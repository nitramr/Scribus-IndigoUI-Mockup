#ifndef PANEL_CONTENT_H
#define PANEL_CONTENT_H

#include <QWidget>
#include "panel.h"

namespace Ui {
class PanelContent;
}

class PanelContent : public Panel
{
    Q_OBJECT

public:

    enum ContentMode {
        Text = 0,
        Image = 1,
        Table =2
    };

    explicit PanelContent(QWidget *parent = nullptr);
    ~PanelContent();

    ContentMode contentMode();

public slots:
    void setContentMode(PanelContent::ContentMode mode);

private:
    Ui::PanelContent *ui;

    void setup();

    ContentMode m_contentMode;
};

#endif // PANEL_CONTENT_H
