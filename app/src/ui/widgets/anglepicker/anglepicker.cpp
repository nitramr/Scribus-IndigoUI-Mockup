#include "anglepicker.h"
#include "math.h"
#include <QMouseEvent>
#include <QPainter>
#include <QRectF>
#include "qapplication.h"
#include "color_utils.h"


AnglePicker::AnglePicker(QWidget *parent)
    : QWidget(parent)
{
    init();
}



AnglePicker::AnglePicker(double angle, QWidget *parent)
    : QWidget(parent)
{
    init();
    setAngle(angle);
}



void AnglePicker::init(){

    int_diameter = 24;
    int_lineThickness = 1;
    dbl_angle = 0;
    dbl_transparency = 0.55; // 10%

    this->setFixedSize(int_diameter, int_diameter);

}



void AnglePicker::paintEvent(QPaintEvent*) {

    QPainter painter(this);
    QColor c_line = QColor(this->palette().color(QPalette::WindowText));
    QColor c_fill = ColorUtils::colorBlend(QColor(this->palette().color(QPalette::Base)),
                                        QColor(this->palette().color(QPalette::Highlight)),
                                        dbl_transparency);

    QBrush brush(c_fill);

    QPen pen;
    pen.setColor(c_line);
    pen.setWidth(int_lineThickness);

    QRectF r = this->rect();
    r = r.adjusted(0.5+int_lineThickness/2,0.5+int_lineThickness/2,-0.5-int_lineThickness/2,-0.5-int_lineThickness/2);

    painter.setRenderHint(QPainter::Antialiasing);

    // draw filled angle
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);
    painter.drawPie(r, 0, 6000 / 360 * dbl_angle);
    painter.restore();

    painter.setPen(pen);

    // draw outer circle
    painter.drawEllipse(r);

    // draw angle line
    painter.save();
    painter.translate(rect().center().x(), rect().center().y());
    painter.rotate(-dbl_angle);
    painter.drawLine(0, 0, int_diameter/2 - int_lineThickness - 1, 0);
    painter.restore();

    // draw center dot
    painter.drawEllipse(QRect(rect().center().x() - (int_lineThickness/2), rect().center().y() - (int_lineThickness/2), int_lineThickness, int_lineThickness));


}



void AnglePicker::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton)
    {

        QLineF *line = new QLineF(rect().center(), event->pos());

        // rotate 0° to 12 o'clock
        double angle = line->angle();// -90;
       // if (angle > 0) angle -= 360;

        // invert counter direction
        dbl_angle = angle;

        update();

        emit angleChanged();

       // qDebug() << "mouseDown" << pnt_pointer << "Angle is:" << int_angle << endl;


    }
}


/**********************
 *
 * Properties
 *
 * *******************/


double AnglePicker::Angle() {

    return dbl_angle;
}



void AnglePicker::setAngle(double degree){

    if (degree < 0) degree = 0;
    if (degree > 360) degree = 360;

    dbl_angle = degree;
    update();

}
