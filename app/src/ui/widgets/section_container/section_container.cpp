#include "section_container.h"

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
    //    , headerLayout (new QHBoxLayout)
    //    , layoutHeaderPrefix (new QHBoxLayout)
    //    , layoutHeaderSuffix (new QHBoxLayout)
    //    , bodyWidget(new QStackedWidget)
    //    , labelTitle (new QLabel("Title"))
    //    , buttonCollapse (new QToolButton)
    //    , headerWidget (new QWidget)
    //    , iconCollapsed(QIcon())
    //    , iconExpanded (QIcon())
    //    , boolIsCollapsible(isCollapsible)
    //    , boolIsCollapsed(false)
    //    , boolHasStyle(true)
{
    int padding = 4;
    headerLayout = new QHBoxLayout;
    layoutHeaderPrefix =new QHBoxLayout;
    layoutHeaderSuffix =new QHBoxLayout;
    bodyWidget=new QStackedWidget;
    labelTitle =new QLabel(title);
    buttonCollapse =new QToolButton;
    headerWidget =new QWidget;
    iconCollapsed=QIcon();
    iconExpanded =QIcon();
    boolIsCollapsible=isCollapsible;
    boolIsCollapsed=false;
    boolHasStyle=true;



    // Label
    //    QFont m_font(this->font());
    //    m_font.setBold( true );
    //    labelTitle->setFont(m_font);
    labelTitle->setText(title);

    // Buttons
    buttonCollapse->setAutoRaise(true);
    buttonCollapse->adjustSize(); // needed to calculate the header height later

    // Header Prefix layout
    layoutHeaderPrefix->setContentsMargins( 0,0,0,0 );
    layoutHeaderPrefix->setSpacing(padding);

    // Header Suffix Layout
    layoutHeaderSuffix->setContentsMargins( 0,0,0,0 );
    layoutHeaderSuffix->setSpacing(padding);

    // Header Layout
    headerLayout->addWidget( buttonCollapse );
    headerLayout->addLayout( layoutHeaderPrefix );
    headerLayout->addWidget( labelTitle );
    headerLayout->addStretch( 0 );
    headerLayout->addLayout( layoutHeaderSuffix );
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

void SectionContainer::addHeaderSuffixWidget(QWidget *widget)
{
    insertHeaderSuffixWidget(-1, widget);
}

void SectionContainer::insertHeaderSuffixWidget(int index, QWidget *widget)
{
    QToolButton *toolButton = static_cast<QToolButton*>(widget);

    if(toolButton){
        toolButton->setAutoRaise(true);
        //m_addonLayout->insertWidget( m_headerLayout->count(), toolButton );
        layoutHeaderSuffix->insertWidget(index, toolButton);
    }else{
        //m_addonLayout->insertWidget( m_headerLayout->count(), widget );
        layoutHeaderSuffix->insertWidget(index, widget);
    }
}

void SectionContainer::removeHeaderSuffixWidget(QWidget *widget)
{
    layoutHeaderSuffix->removeWidget( widget );
    widget->deleteLater();
}

void SectionContainer::addHeaderSuffixSpacing(int size)
{
    insertHeaderSuffixSpacing(-1, size);
}

void SectionContainer::insertHeaderSuffixSpacing(int index, int size)
{
    layoutHeaderSuffix->insertSpacing(index, size);
}

void SectionContainer::addHeaderPrefixWidget(QWidget *widget)
{
    insertHeaderPrefixWidget(-1, widget);
}

void SectionContainer::insertHeaderPrefixWidget(int index, QWidget *widget)
{
    QToolButton *toolButton = static_cast<QToolButton*>(widget);

    if(toolButton){
        toolButton->setAutoRaise(true);
        //m_addonLayout->insertWidget( m_headerLayout->count(), toolButton );
        layoutHeaderPrefix->insertWidget(index, toolButton);
    }else{
        //m_addonLayout->insertWidget( m_headerLayout->count(), widget );
        layoutHeaderPrefix->insertWidget(index, widget);
    }
}

void SectionContainer::removeHeaderPrefixWidget(QWidget *widget)
{
    layoutHeaderPrefix->removeWidget( widget );
    widget->deleteLater();
}

void SectionContainer::addHeaderPrefixSpacing(int size)
{
    insertHeaderPrefixSpacing(-1, size);
}

void SectionContainer::insertHeaderPrefixSpacing(int index, int size)
{
    layoutHeaderPrefix->insertSpacing(index, size);
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

void SectionContainer::setFont(QFont font)
{
    labelTitle->setFont(font);
    QWidget::setFont(font);
}

QFont SectionContainer::font()
{
    return labelTitle->font();
}

void SectionContainer::setHasStyle(bool isSimple)
{
    boolHasStyle = isSimple;
    update();
}

bool SectionContainer::hasStyle()
{
    return boolHasStyle;
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

            if(boolHasStyle){

                //            QColor topLineColor( palette().color(QPalette::Mid) );
                QColor bottomLineColor( palette().color(QPalette::Dark) );
                //            lineColor.setAlphaF(0.12f);

                QColor bgColor( palette().color(QPalette::WindowText) );
                bgColor.setAlphaF(0.07f);

                int lineWidth = 1;
                int headerheight = headerWidget->height();
                QRect headerRect(0, 0, this->width(), headerheight - lineWidth);

                QPainter painter( headerWidget );

                painter.setPen( Qt::NoPen );
                painter.setBrush(bgColor);
                painter.drawRect(headerRect);

                painter.setBrush(Qt::NoBrush);

                //            // Top Line
                //            painter.setPen( QPen(topLineColor, lineWidth) );
                //            painter.drawLine( 0, 0,this->width(), 0 );

                // Bottom Line
                painter.setPen( QPen(bottomLineColor, lineWidth) );
                painter.drawLine( 0, headerheight - lineWidth, this->width(), headerheight - lineWidth );
            }
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

    if(!boolHasStyle){

        int lineWidth = 1;
        QColor bottomLineColor( palette().color(QPalette::Dark) );

        QPainter painter( this );

        // Bottom Line
        painter.setPen( QPen(bottomLineColor, lineWidth) );
        painter.drawLine( 8, this->height() - lineWidth, this->width() - 8, this->height() - lineWidth );

    }

}
