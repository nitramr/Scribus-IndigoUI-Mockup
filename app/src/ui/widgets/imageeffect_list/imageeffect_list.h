#ifndef IMAGEEFFECTLIST_H
#define IMAGEEFFECTLIST_H

#include <QWidget>
#include <QVBoxLayout>

class ImageEffectList : public QWidget
{
    Q_OBJECT
public:
    explicit ImageEffectList(QWidget *parent = nullptr);

    void addItem(QWidget * item);

private:

    QVBoxLayout *layoutList;
    QWidget *scrollContainer;


    void setup();
    bool eventFilter(QObject *object, QEvent *event);

signals:

};

#endif // IMAGEEFFECTLIST_H
