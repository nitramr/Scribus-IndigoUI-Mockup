#include "dummydocument.h"
#include <QPainter>

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

    int w = 800;
    int h = w*1.414;

    QRect paper(rect().center().x()-w/2, rect().center().y()-h/2, w, h);

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

