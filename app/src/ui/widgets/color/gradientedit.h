#ifndef GRADIENTEDIT_H
#define GRADIENTEDIT_H

#include "sccolor.h"
#include "vgradient.h"
#include <QWidget>

class GradientEdit : public QWidget
{
    Q_OBJECT
public:
    explicit GradientEdit(QWidget *parent = nullptr);
    ~GradientEdit() {};
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *m);
    void mouseReleaseEvent(QMouseEvent *m);
    void mouseMoveEvent(QMouseEvent *m);
//    void leaveEvent(QEvent*);
//    void enterEvent(QEnterEvent*);
//    void resizeEvent(QResizeEvent *e);

    void setActiveStopColor(const ScColor& c);

    void setActiveStopPosition(double t);

    void setIsEditable(bool isEditable);
    bool isEditable();

    void setGradient(const VGradient& gradient);
    const VGradient& gradient();

private:
    VGradient fill_gradient;
    QRect canvasRect();
    bool m_isEditable;
    bool isMouseOutside(QPoint mouse);
    int m_activeStop;
    int m_tmpStop;

    void setup();
    void addStop(QPoint mousePosition);
    void removeStop();
    void emitStop();
    void emitStopID();
    void updateTmpStop(double t);
    void sortStops();

    int stopAtPosition(QPoint position);
    double percentFromPosition(QPointF position);

signals:
    void selectedColor(ScColor);
    void selectedStop(VColorStop*);
    void selectedPosition(double);

};

#endif // GRADIENTEDIT_H
