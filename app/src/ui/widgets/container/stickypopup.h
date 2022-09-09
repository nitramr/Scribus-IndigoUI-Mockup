#ifndef STICKYPOPUP_H
#define STICKYPOPUP_H

#include <QWidget>
#include <QVBoxLayout>

class StickyPopup : public QWidget
{
    Q_OBJECT
public:   

    explicit StickyPopup(QWidget * child, QWidget *parent);

    ~StickyPopup();

    QWidget * parent();
    QWidget * child();

protected:
    void paintEvent(QPaintEvent* event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private:

    enum PointerDirection {
        None = 0,
        Left = 1,
        Top = 2,
        Right = 3,
        Bottom = 4
    };

    PointerDirection m_pointerDirection = {PointerDirection::None};
    QWidget * m_child;
    QWidget * m_handle;
    QVBoxLayout * m_layout;
    QPoint m_mousePos;

    void setPointerDirection(PointerDirection direction);

//    QPoint pointerPosition();

    QPolygon mask();

    void calculatePosition();


signals:

public slots:
    void show();
    void updateSize();

};

#endif // STICKYPOPUP_H
