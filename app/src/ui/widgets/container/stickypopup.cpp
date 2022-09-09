#include "stickypopup.h"
#include "iconmanager.h"

#include <QPainter>
#include <QPaintEvent>
#include <QVBoxLayout>
#include <QApplication>
#include <QToolButton>

namespace
{
const int POINTER_HEIGHT = 24;
}

StickyPopup::StickyPopup(QWidget *child, QWidget *parent)
    : QWidget{parent, Qt::Window | Qt::Tool | Qt::FramelessWindowHint}, // Qt::Tool | Qt::FramelessWindowHint
      m_child(child)
{

    if(m_child == nullptr) m_child = new QWidget();

    IconManager &iconManager = IconManager::instance();

    m_pointerDirection = PointerDirection::None;

    m_handle = new QWidget();
    // m_handle->setFixedHeight(30);
    m_handle->installEventFilter(this);


    QToolButton *buttonClose = new QToolButton();
    buttonClose->setToolButtonStyle(Qt::ToolButtonIconOnly);
    buttonClose->setIcon(iconManager.icon("close"));
    buttonClose->setFixedSize(16,16);
    buttonClose->setAutoRaise(true);

    QHBoxLayout *layoutHeader = new QHBoxLayout;
    layoutHeader->addWidget(m_handle);
    layoutHeader->addWidget(buttonClose);
    layoutHeader->setContentsMargins(8, 8, 8, 8);

    m_layout = new QVBoxLayout();
    m_layout->addLayout(layoutHeader);
    m_layout->addWidget(m_child);
    m_layout->setSpacing(0);
    m_layout->setContentsMargins(1, 1, 1, 1);

    setLayout(m_layout);
    setWindowTitle(child->windowTitle());

    connect(buttonClose, &QToolButton::pressed, this, [this]() {
        this->hide();

    });

}

StickyPopup::~StickyPopup()
{
   // deleteLater();
}

QWidget *StickyPopup::parent()
{
    return qobject_cast<QWidget*>(QWidget::parent());
}

QWidget *StickyPopup::child()
{
    return m_child;
}

QPolygon StickyPopup::mask()
{
    int pHeight = POINTER_HEIGHT;
    int pWidth = POINTER_HEIGHT;
    int w = width();
    int h = height();

    QPolygon pp;

    // TODO: replace with position of parent widget
    QPoint pointerPos(w/2, h/2);

    switch(m_pointerDirection){
    default:
    case PointerDirection::None:
        pp << QPoint(0, 0); // top left
        pp << QPoint(w, 0); // top right
        pp << QPoint(w, h); // bottom right
        pp << QPoint(0, h); // bottom left
        break;
    case PointerDirection::Left:
        pp << QPoint(pWidth, 0); // top left
        pp << QPoint(w, 0); // top right
        pp << QPoint(w, h); // bottom right
        pp << QPoint(pWidth, h); // bottom left
        pp << QPoint(pWidth, pointerPos.y() + pHeight/2);
        pp << QPoint(0, pointerPos.y());
        pp << QPoint(pWidth, pointerPos.y() - pHeight/2);
        break;
    case PointerDirection::Top:
        pp << QPoint(0, pHeight); // top left
        pp << QPoint(pointerPos.x() - pWidth/2, pHeight);
        pp << QPoint(pointerPos.x(), 0);
        pp << QPoint(pointerPos.x() + pWidth/2, pHeight);
        pp << QPoint(w, pHeight); // top right
        pp << QPoint(w, h); // bottom right
        pp << QPoint(0, h); // bottom left
        break;
    case PointerDirection::Right:
        pp << QPoint(0, 0); // top left
        pp << QPoint(w - pWidth, 0); // top right
        pp << QPoint(w - pWidth, pointerPos.y() - pHeight/2);
        pp << QPoint(w, pointerPos.y());
        pp << QPoint(w - pWidth, pointerPos.y() + pHeight/2);
        pp << QPoint(w - pWidth, h); // bottom right
        pp << QPoint(0, h); // bottom left
        break;
    case PointerDirection::Bottom:
        pp << QPoint(0, 0); // top left
        pp << QPoint(w, 0); // top right
        pp << QPoint(w, h - pHeight); // bottom right
        pp << QPoint(pointerPos.x() + pWidth/2, h - pHeight);
        pp << QPoint(pointerPos.x(), h);
        pp << QPoint(pointerPos.x() - pWidth/2, h - pHeight);
        pp << QPoint(0, h - pHeight); // bottom left
        break;
    }


    return pp;
}


void StickyPopup::paintEvent(QPaintEvent *event)
{

    QRegion widgetMask(mask());
    setMask(widgetMask);

    QPainter painter(this);

    painter.setPen(QPen(palette().color(QPalette::Mid), 2) );
    painter.setBrush(palette().color(QPalette::Window) );
//    painter.drawRect(this->rect().adjusted(0,0,-1,-1));
    painter.drawPolygon(mask());

}

bool StickyPopup::eventFilter(QObject *obj, QEvent *event)
{

    switch(event->type()){
    case QEvent::MouseButtonPress:{
        QMouseEvent *mEvent = (QMouseEvent*)event;
        m_mousePos = mEvent->pos();
    }
        break;
    case QEvent::MouseMove:{

        QMouseEvent *mEvent = (QMouseEvent*)event;
        if(mEvent->buttons() & Qt::LeftButton)
        {
            setPointerDirection(PointerDirection::None);
            this->move(mapToParent(mEvent->pos() - m_mousePos));
        }
    }
        break;
    default:

        break;
    }

    return QObject::eventFilter(obj, event);

}

void StickyPopup::setPointerDirection(PointerDirection direction)
{
    if(m_pointerDirection == direction) return;

    m_pointerDirection = direction;

    switch(m_pointerDirection){
    default:
    case PointerDirection::None:
        setContentsMargins(0, 0, 0, 0);
        break;
    case PointerDirection::Left:
        setContentsMargins(POINTER_HEIGHT, 0, 0, 0);
        break;
    case PointerDirection::Top:
        setContentsMargins(0, POINTER_HEIGHT, 0, 0);
        break;
    case PointerDirection::Right:
        setContentsMargins(0, 0, POINTER_HEIGHT, 0);
        break;
    case PointerDirection::Bottom:
        setContentsMargins(0, 0, 0, POINTER_HEIGHT);
        break;
    }

    updateSize();
}

//QPoint StickyPopup::pointerPosition()
//{
//    QPoint parentGlobalPos = parent()->mapToGlobal(QPoint());
//    QPoint globalPos = this->mapToGlobal((QPoint()));

//    //    QRect rect = this->geometry();

//    //    qDebug() << rect;

//    QPoint result = parentGlobalPos - globalPos;
//    //    qDebug() << result;
//    return result;
//}

void StickyPopup::calculatePosition()
{
    updateSize();

    QPoint parentGlobalPos = parent()->mapToGlobal(QPoint());
    QPoint position = parentGlobalPos;

    QSize screen = QGuiApplication::primaryScreen()->size();
    int screenHeight = screen.height();
    int screenWidth = screen.width();

    // Check if widget can be displayed on a side of parent
    bool canBeLeft = (parentGlobalPos.x() >= this->width() + POINTER_HEIGHT) ? true : false;
    bool canBeTop = (parentGlobalPos.y() >= this->height() + POINTER_HEIGHT) ? true : false;
    bool canBeRight = (parentGlobalPos.x() + parent()->width() + this->width() + POINTER_HEIGHT <= screenWidth) ? true : false;
    bool canBeBottom = (parentGlobalPos.y() + parent()->height() + this->height() + POINTER_HEIGHT <= screenHeight) ? true : false;

    //  qDebug() << "Parent:" << parentGlobalPos << "Widget:" << this->size() << "L:" << canBeLeft << "T:" << canBeTop << "R:" << canBeRight << "B:" << canBeBottom;


    // Show left (L:yes T:na R:no B:na)
    if(canBeLeft == true && canBeRight == false){
        // setPointerDirection(PointerDirection::Right);
        position.setX( parentGlobalPos.x() - this->width());

    }

    // Show Right (L:no T:na R:yes B:na)
    if(canBeRight == true){
        // setPointerDirection(PointerDirection::Left);
        position.setX( parentGlobalPos.x() + parent()->width());

    }

    // Show Top (L:yes T:yes R:yes B:no)
    if(canBeTop == true && canBeBottom == false && canBeLeft == true && canBeRight == true){
        // setPointerDirection(PointerDirection::Bottom);
        position.setY( parentGlobalPos.y() - this->height());

    }

    // Show Bottom (L:yes T:no R:yes B:yes)
    if(canBeBottom == true && canBeLeft == true && canBeRight == true){
        // setPointerDirection(PointerDirection::Top);
        position.setY( parentGlobalPos.y() + parent()->height());

    }


    setGeometry(position.x(),position.y(), this->width(), this->height() );

}

void StickyPopup::show()
{

    calculatePosition();

    QWidget::show();
}

void StickyPopup::updateSize()
{
    //resize(minimumSizeHint());
    adjustSize();
}
