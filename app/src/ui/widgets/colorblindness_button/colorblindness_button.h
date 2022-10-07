#ifndef COLORBLINDNESSBUTTON_H
#define COLORBLINDNESSBUTTON_H

#include "colorblind.h"
#include <QToolButton>
#include <QWidget>

class ColorBlindnessButton : public QToolButton
{
    Q_OBJECT

public:
    ColorBlindnessButton(QWidget * parent = nullptr);

private:
    QMenu *menuColorBlind;
    QAction *actionColorBlindNormal;
    QAction *actionColorBlindRed;
    QAction *actionColorBlindGreen;
    QAction *actionColorBlindBlue;
    QAction *actionColorBlindFull;

    void connectSlots();

private slots:
    void changeColorBlindness();

signals:

    void colorBlindnessDefect(VisionDefectColor::defectMode);

};

#endif // COLORBLINDNESSBUTTON_H
