#ifndef EYEDROPPERWIDGET_H
#define EYEDROPPERWIDGET_H

#include "sccolor.h"
#include <QWidget>

class EyeDropperScreenWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EyeDropperScreenWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *e);
    void mouseReleaseEvent(QMouseEvent *m);
    void mouseMoveEvent(QMouseEvent *m);
    void keyPressEvent( QKeyEvent * e );

public slots:
    void show();


private:

    struct screenshotData {
        QPixmap pixmap;
        QRect rect;
    };

    QPixmap m_screenshot;
    QPoint m_MousePos;
    int m_zoomFactor;
    QSize m_magnifierSize;
    ScColor m_color;
    bool m_grid;

    const QRect magnifierRect(int zoomFactor = 1);
    const QRect labelRect(QFont font, QString text);
    ScColor grabScreenColor(const QPoint &p);

    void takeScreenshot();

signals:

    void screenColor(ScColor color);

};

#endif // EYEDROPPERWIDGET_H
