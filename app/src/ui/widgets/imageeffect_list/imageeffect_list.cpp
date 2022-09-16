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
    layoutList->insertWidget(layoutList->count()-1, item);
}

void ImageEffectList::setup()
{

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layoutList = new QVBoxLayout();
    layoutList->addStretch(1);
    layoutList->setSpacing(1);

    scrollContainer = new QWidget();
    scrollContainer->setLayout(layoutList);
    scrollContainer->setSizePolicy( sizePolicy );
    scrollContainer->installEventFilter(this);

    QScrollArea *m_scrollArea = new QScrollArea();
    m_scrollArea->setWidget(scrollContainer);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setSizePolicy( sizePolicy );

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
        case QEvent::Paint:{

//            QPainter painter(this);
//            painter.fillRect(this->rect(), QPalette::Base);
//            painter.end();

            return true;

            break;
        }
        default:
            return false;
        }


    }

    return false;
}
