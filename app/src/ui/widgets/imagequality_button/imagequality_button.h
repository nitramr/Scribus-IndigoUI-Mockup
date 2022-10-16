#ifndef IMAGEQUALITYBUTTON_H
#define IMAGEQUALITYBUTTON_H

#include <QToolButton>
#include <QWidget>
#include "enums.h"

class ImageQualityButton : public QToolButton
{
    Q_OBJECT
public:
    ImageQualityButton(QWidget *parent = nullptr);

private:
    QMenu *menuQuality;
    QAction *actionQualityHigh;
    QAction *actionQualityNormal;
    QAction *actionQualityLow;

    void connectSlots();

private slots:
    void changeImageQuality();

signals:

    void imageQuality(ImageRenderQuality imageQuality);
};

#endif // IMAGEQUALITYBUTTON_H
