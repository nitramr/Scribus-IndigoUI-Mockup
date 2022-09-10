#ifndef EYEDROPPERWIDGET_H
#define EYEDROPPERWIDGET_H

#include "sccolor.h"
#include <QWidget>

class EyeDropperWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EyeDropperWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *m);
    void mouseReleaseEvent(QMouseEvent *m);
    void mouseMoveEvent(QMouseEvent *m);

public slots:
    void show();


private:

    QPixmap m_screenshot;
    QPoint m_MousePos;

    ScColor grabScreenColor(const QPoint &p);

signals:

    void screenColor(ScColor color);

};

#endif // EYEDROPPERWIDGET_H
