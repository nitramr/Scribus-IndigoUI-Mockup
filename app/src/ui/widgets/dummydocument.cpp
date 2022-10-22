#include "dummydocument.h"
#include <QPainter>
#include <QMouseEvent>
#include "menu_manager.h"
#include "managepageproperties_dialog.h"

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

DummyDocument::DummyDocument(QWidget *parent)
    : QWidget{parent}
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    setFixedSize(1400, 1400);
    setContextMenuPolicy(Qt::CustomContextMenu);

    dialogManagePageProperties = new ManagePagePropertiesDialog(this);

    contextDocument = new QMenu();
    contextPaper = new QMenu();
    contextImage = new QMenu();

    MenuManager &menuManager = MenuManager::instance();
    menuManager.initPageContextMenu(contextPaper, this);
    menuManager.initDocumentContextMenu(contextDocument, this);
    menuManager.initImageItemContextMenu(contextImage);

    connectSlots();
}


void DummyDocument::connectSlots()
{
    connect(this, &DummyDocument::customContextMenuRequested, this, &DummyDocument::showContextMenu);
}

/* ********************************************************************************* *
 *
 * Public Slots
 *
 * ********************************************************************************* */

void DummyDocument::setGridVisibility(bool enable)
{
    m_grid = enable;
    update();
}

void DummyDocument::setBaselineVisibility(bool enable)
{
    m_baseline = enable;
    update();
}

void DummyDocument::setGuideVisibility(bool enable)
{
    m_guide = enable;
    update();
}

void DummyDocument::toggleGridVisibility()
{
    setGridVisibility(!m_grid);
}

void DummyDocument::toggleBaselineVisibility()
{
    setBaselineVisibility(!m_baseline);
}

void DummyDocument::toggleGuideVisibility()
{
    setGuideVisibility(!m_guide);
}

void DummyDocument::showManagePageDialog()
{
    if(dialogManagePageProperties->exec()){

    }

}

/* ********************************************************************************* *
 *
 * Private Members
 *
 * ********************************************************************************* */

QRect DummyDocument::rectDocument()
{
    int w = 800;
    int h = w*1.414;

    return QRect(rect().center().x()-w/2, rect().center().y()-h/2, w, h);
}

QRect DummyDocument::rectImage()
{
    QPoint tl = rectDocument().topLeft();
    QPoint offset(50,50);

    return QRect(tl + offset, QSize(489/2, 464/2));
}

/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

void DummyDocument::showContextMenu(const QPoint &pos)
{
    switch(m_contextMenuType){
    case ContextMenuType::Document:
        contextDocument->exec(mapToGlobal(pos));
        break;
    case ContextMenuType::Page:
        contextPaper->exec(mapToGlobal(pos));
        break;
    case ContextMenuType::Image:
        contextImage->exec(mapToGlobal(pos));
        break;

    }
}


/* ********************************************************************************* *
 *
 * Events
 *
 * ********************************************************************************* */

void DummyDocument::paintEvent(QPaintEvent *)
{
    //    QColor cMargin(255, 85, 153);
    //    QColor cGuides(229, 128, 255);
    //    QColor cGrid(205, 222, 135);
    //    QColor cOutline(0, 0, 0);
    //    QColor cShadow(80,80,80);
    //    QColor cBackground(Qt::darkGray);
    //    QColor cBaseLine(179, 179, 179);

    QColor cGuides(46, 181, 229);
    QColor cMargin(229, 92, 184);
    QColor cGrid(102, 204, 82);
    QColor cOutline(255, 51, 51);
    QColor cShadow(80,80,80);
    QColor cBackground(Qt::darkGray);
    QColor cBaseLine(179, 179, 179);


    QPainter painter(this);

    QRect paper = rectDocument();

    int left = int(paper.left());
    int top = int(paper.top());


    // Draw Background
    painter.fillRect(rect(), cBackground);


    // Draw Paper Shadow
    painter.fillRect(paper.adjusted(6,6,6,6), QBrush(cShadow));


    // Draw Paper
    painter.fillRect(paper,  Qt::white);
    painter.setBrush(Qt::NoBrush);


    // BaseLine
    QPen pen(cBaseLine);
    if(m_baseline) {
        int bgrid = 24;

        QVarLengthArray<QLineF, 1> blines;
        for (int y = top; y < paper.bottom(); y += bgrid)
            blines.append(QLineF(paper.left(), y, paper.right(), y));

        painter.setPen(pen);
        painter.drawLines(blines.data(), blines.size());
    }

    // Draw Image
    QPixmap image(":/images/splashscreen_dark");
    painter.drawPixmap(rectImage(), image);

    // Draw Shape
    //painter.fillRect(rectImage(),  QColor(128,200,200));


    // Draw Grid
    if(m_grid){
        int sgrid = 20;
        int lgrid = 100;

        // Large Grid
        QVarLengthArray<QLineF, 1> llines;
        for (int x = left; x < paper.right(); x += lgrid)
            llines.append(QLineF(x, paper.top(), x, paper.bottom()));
        for (int y = top; y < paper.bottom(); y += lgrid)
            llines.append(QLineF(paper.left(), y, paper.right(), y));

        // Small Grid
        QVarLengthArray<QLineF, 1> slines;
        for (int x = left; x < paper.right(); x += sgrid)
            slines.append(QLineF(x, paper.top(), x, paper.bottom()));
        for (int y = top; y < paper.bottom(); y += sgrid)
            slines.append(QLineF(paper.left(), y, paper.right(), y));

        pen.setColor(cGrid);
        painter.setPen(pen);
        painter.drawLines(llines.data(), llines.size());
        pen.setStyle(Qt::DotLine);
        painter.setPen(pen);
        painter.drawLines(slines.data(), slines.size());
    }


    // Draw Margin
    painter.setPen(cMargin);
    painter.drawRect(paper.adjusted(50, 50, -50, -50));


    // Draw Outline
    painter.setPen(cOutline);
    painter.drawRect(paper);


    // Guides
    if(m_guide){
        painter.setPen(cGuides);
        painter.drawLine(QPoint(510,0), QPoint(510, rect().bottom()));
    }


}

void DummyDocument::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::RightButton)
    {

        if(rect().contains(event->pos())){
            m_contextMenuType = ContextMenuType::Document;
        }

        if(rectDocument().contains(event->pos())){
            m_contextMenuType = ContextMenuType::Page;
        }

        if(rectImage().contains(event->pos())){
            m_contextMenuType = ContextMenuType::Image;
        }

    }

    QWidget::mousePressEvent(event);
}




