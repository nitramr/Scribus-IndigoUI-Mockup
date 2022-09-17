#include "imageeffect_list.h"
#include <QScrollArea>
#include <QMouseEvent>
#include <QPainter>

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */


ImageEffectList::ImageEffectList(QWidget *parent)
    : QWidget{parent}
{

    setup();
}

void ImageEffectList::addItem(QWidget *item)
{
    layoutList->addWidget(item);
}

void ImageEffectList::setup()
{

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layoutList = new QVBoxLayout();
    layoutList->setSpacing(0);

    // Layout that only separate stretch item from item list
    QVBoxLayout *layoutBase = new QVBoxLayout();
    layoutBase->addLayout(layoutList);
    layoutBase->addStretch(1);
    layoutBase->setSpacing(0);
    layoutBase->setContentsMargins(0,0,0,0);

    scrollContainer = new QWidget();
    scrollContainer->setLayout(layoutBase);
    scrollContainer->setSizePolicy( sizePolicy );
    scrollContainer->setContentsMargins(0,0,0,0);
//    scrollContainer->installEventFilter(this);

    QScrollArea *m_scrollArea = new QScrollArea();
    m_scrollArea->setWidget(scrollContainer);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setSizePolicy( sizePolicy );
    m_scrollArea->setFrameShape(QFrame::NoFrame);

    QVBoxLayout *box = new QVBoxLayout();
    box->addWidget(m_scrollArea);
    box->setContentsMargins(0,0,0,0);

    this->setLayout(box);
    this->setSizePolicy( sizePolicy );


}

/* ********************************************************************************* *
 *
 * Events
 *
 * ********************************************************************************* */


bool ImageEffectList::eventFilter(QObject *object, QEvent *event)
{
    // Header Widget
   if(object == scrollContainer){
        switch(event->type())
        {
        case QEvent::MouseButtonDblClick:{
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton) {

                return true;
            }
            break;
        }
        default:
            return false;
        }


    }

    return false;
}
