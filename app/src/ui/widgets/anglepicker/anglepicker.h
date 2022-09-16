#ifndef ANGLEPICKER_H
#define ANGLEPICKER_H

#include <QWidget>

class AnglePicker : public QWidget
{
    Q_OBJECT
    Q_CLASSINFO("Version", "1.0.0")

public:
    AnglePicker(QWidget *parent = 0);
    AnglePicker(double angle, QWidget *parent = 0);
    void setAngle(double degree);
    double Angle();

private:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *event);
    void init();

    int int_lineThickness;
    double dbl_angle;
    int int_diameter;
    double dbl_transparency;

signals:
    void angleChanged();

public slots:
};


#endif // ANGLEPICKER_H
