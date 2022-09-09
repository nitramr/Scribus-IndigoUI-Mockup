#include "sectioncontainer.h"

#include <QPainter>
#include <QPen>
#include <QMouseEvent>
// #include "color_utils.h"


/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

SectionContainer::SectionContainer(QWidget *parent) : SectionContainer("Title", true, parent){}

SectionContainer::SectionContainer(QString title, bool isCollapsible, QWidget *parent)
    : QWidget{parent}
    , headerLayout (new QHBoxLayout)
    , addonLayout (new QHBoxLayout)
    , bodyWidget(new QStackedWidget)
    , labelTitle (new QLabel("Title"))
    , buttonCollapse (new QToolButton)
    , headerWidget (new QWidget)
    , iconCollapsed(QIcon())
    , iconExpanded (QIcon())
    , boolIsCollapsible(isCollapsible)
    , boolIsCollapsed(false)
{
    int padding = 4;

    // Label
    QFont m_font(this->font());
    m_font.setBold( true );
    labelTitle->setFont(m_font);
    labelTitle->setText(title);

    // Buttons
    buttonCollapse->setAutoRaise(true);
    buttonCollapse->adjustSize(); // needed to calculate the header height later

    // Addon Layout
    addonLayout->setContentsMargins( 0,0,0,0 );
    addonLayout->setSpacing(padding);

    // Header Layout
    headerLayout->addWidget( buttonCollapse );
    headerLayout->addWidget( labelTitle );
    headerLayout->addStretch( 0 );
    headerLayout->addLayout( addonLayout );
    headerLayout->setContentsMargins( padding, padding/2, padding, padding/2 );

    // Header Widget
    headerWidget->setLayout(headerLayout);
    headerWidget->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Maximum );
    headerWidget->setMaximumHeight(buttonCollapse->height() + padding);
    headerWidget->installEventFilter(this);


    // Main Layout
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(headerWidget);
    mainLayout->addWidget(bodyWidget);


    // Size Policy
    QSizePolicy sizePol = QSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Maximum );
    setSizePolicy(sizePol);
    tmpSizePolicy = sizePol;

    // initial Setup
    setIsCollapsible(isCollapsible);
    connectSlots();


}

void SectionContainer::connectSlots()
{
    connect( buttonCollapse, &QToolButton::clicked,this, &SectionContainer::toggleCollpasedState );
}

/* ********************************************************************************* *
 *
 * Header
 *
 * ********************************************************************************* */

void SectionContainer::addHeaderWidget(QWidget *widget)
{
    insertHeaderWidget(-1, widget);
}

void SectionContainer::insertHeaderWidget(int index, QWidget *widget)
{
    QToolButton *toolButton = static_cast<QToolButton*>(widget);

    if(toolButton){
        toolButton->setAutoRaise(true);
        //m_addonLayout->insertWidget( m_headerLayout->count(), toolButton );
        addonLayout->insertWidget(index, toolButton);
    }else{
        //m_addonLayout->insertWidget( m_headerLayout->count(), widget );
        addonLayout->insertWidget(index, widget);
    }
}

void SectionContainer::removeHeaderWidget(QWidget *widget)
{
    addonLayout->removeWidget( widget );
    widget->deleteLater();
}

void SectionContainer::addHeaderSpacing(int size)
{
    insertHeaderSpacing(-1, size);
}

void SectionContainer::insertHeaderSpacing(int index, int size)
{
    addonLayout->insertSpacing(index, size);
}



/* ********************************************************************************* *
 *
 * Properties
 *
 * ********************************************************************************* */

void SectionContainer::setText(QString text)
{
    labelTitle->setText(text);
}

QString SectionContainer::text() const
{
    return labelTitle->text();
}

void SectionContainer::setIsCollapsible(bool isCollapsible)
{
    boolIsCollapsible = isCollapsible;
    buttonCollapse->setVisible(isCollapsible);
}

bool SectionContainer::isCollapsible()
{
    return boolIsCollapsible;
}

bool SectionContainer::isCollapsed()
{
    return boolIsCollapsed;
}

void SectionContainer::setIsCollapsed(bool state)
{
    if(isCollapsible() == false) return;

    boolIsCollapsed = state;

    if( boolIsCollapsed ){
        // save size policy
     //   tmpSizePolicy = this->sizePolicy();

        bodyWidget->hide();
        buttonCollapse->setIcon(iconCollapsed);

//        // optimize size policy for collapsed state
//        QSizePolicy sizePol = QSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Maximum );
//        setSizePolicy(sizePol);

    } else {
        // restore size policy
      //  this->setSizePolicy(tmpSizePolicy);

        bodyWidget->show();
        buttonCollapse->setIcon(iconExpanded);
    }

    adjustSize();

    emit collapsedState(boolIsCollapsed);
}


void SectionContainer::setCollapseIcons(QIcon collapsed, QIcon expanded)
{
    iconCollapsed = collapsed;
    iconExpanded = expanded;

    if( boolIsCollapsed ){
        buttonCollapse->setIcon(iconCollapsed);
    } else {
        buttonCollapse->setIcon(iconExpanded);
    }
}

/* ********************************************************************************* *
 *
 * Slots
 *
 * ********************************************************************************* */

void SectionContainer::toggleCollpasedState()
{
    if(isCollapsible() == false) return;

    ( boolIsCollapsed ) ? boolIsCollapsed = false : boolIsCollapsed = true;

    setIsCollapsed(boolIsCollapsed);
}


/* ********************************************************************************* *
 *
 * Plugin (StackedWidget)
 *
 * ********************************************************************************* */

QWidget* SectionContainer::widget(int index)
{
    return bodyWidget->widget(index);
}

void SectionContainer::addPage(QWidget *page)
{
    insertPage(count(), page);
}

void SectionContainer::insertPage(int index, QWidget *page)
{
    page->setParent(bodyWidget);

    bodyWidget->insertWidget(index, page);
}

void SectionContainer::removePage(int index)
{
    QWidget *widget = bodyWidget->widget(index);
    bodyWidget->removeWidget(widget);
}

int SectionContainer::count() const
{
    return bodyWidget->count();
}

int SectionContainer::currentIndex() const
{
    return bodyWidget->currentIndex();
}

void SectionContainer::setCurrentIndex(int index)
{
    if (index != currentIndex()) {
        bodyWidget->setCurrentIndex(index);
        emit currentIndexChanged(index);
    }
}


/* ********************************************************************************* *
 *
 * Events
 *
 * ********************************************************************************* */

bool SectionContainer::eventFilter(QObject *object, QEvent *event)
{
    // Header Widget
    if(object == headerWidget){
        switch(event->type())
        {
        case QEvent::MouseButtonDblClick:{
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton && isCollapsible()) {
                toggleCollpasedState();
                return true;
            }
            break;
        }
        case QEvent::Paint:{

            QColor lineColor( palette().mid().color() );
            QColor bgColor( palette().color(QPalette::WindowText) );
            bgColor.setAlphaF(0.15f);

            int lineWidth = 1;
            int headerheight = headerWidget->height() - lineWidth;
            QRect headerRect(0,0,this->width(), headerheight);

            QPainter painter( headerWidget );

            painter.setPen( Qt::NoPen );
            painter.setBrush(bgColor);
            painter.drawRect(headerRect);

            painter.setPen( lineColor );
            painter.setBrush(Qt::NoBrush);
            painter.drawLine( 0, headerheight,this->width(), headerheight );

            return true;

            break;
        }
        default:
            return false;
        }


    }

    return false;
}


void SectionContainer::paintEvent(QPaintEvent *event)
{

    QWidget::paintEvent(event);
//    QColor bgColor( Qt::red);

//    QPainter painter( this );

//    painter.setPen( Qt::NoPen );
//    painter.setBrush(bgColor);
//    painter.drawRect(this->rect());

}
