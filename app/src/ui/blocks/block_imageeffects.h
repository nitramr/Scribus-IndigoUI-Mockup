#ifndef BLOCK_IMAGEEFFECTS_H
#define BLOCK_IMAGEEFFECTS_H

#include <QWidget>
#include <QMenu>

namespace Ui {
class BlockImageEffects;
}

class BlockImageEffects : public QWidget
{
    Q_OBJECT

public:
    explicit BlockImageEffects(QWidget *parent = nullptr);
    ~BlockImageEffects();

private:
    Ui::BlockImageEffects *ui;

    QMenu *menuImageEffects;
    QAction *actionEffectBlur;
    QAction *actionEffectBrightness;
    QAction *actionEffectColorize;
    QAction *actionEffectDuotone;
    QAction *actionEffectTritone;
    QAction *actionEffectQuadtone;
    QAction *actionEffectContrast;
    QAction *actionEffectGrayscale;
    QAction *actionEffectCurves;
    QAction *actionEffectInvert;
    QAction *actionEffectPosterize;
    QAction *actionEffectSharpen;


    void setup();
    void connectSlots();

private slots:
    void addImageEffect();
};

#endif // BLOCK_IMAGEEFFECTS_H
