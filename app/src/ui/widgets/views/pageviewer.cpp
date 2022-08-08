#include "pageviewer.h"
#include <QBoxLayout>
#include <QDrag>
#include <QMimeData>
#include <QScrollArea>
#include <QPainter>
#include <QResizeEvent>
#include <QApplication>
#include <QElapsedTimer>

#include "iconmanager.h"

const double PAGERATIO = 1.414;

/* ********************************************************************************* *
 *
 *
 * Page Cell
 *
 *
 * ********************************************************************************* */
PageCell::PageCell(const QString& text, uint nr, const QPixmap& pix) :
    pageNumber(nr),
    pagePreview(pix),
    pageName(text)
{

}

const QString& PageCell::getPageName()
{
    return pageName;
}

/* ********************************************************************************* *
 *
 *
 * Page Viewer
 *
 *
 * ********************************************************************************* */

PageViewer::PageViewer(QWidget *parent) : QWidget(parent)
{
    m_pageGrid = new PageGrid(this);

    QScrollArea* scroll = new QScrollArea;
    scroll->setWidget(m_pageGrid);

    scroll->setWidgetResizable(true);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scroll->setFrameShape(QFrame::NoFrame);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(scroll);
    layout->setContentsMargins(0,0,0,0);

    setLayout(layout);

}

PageGrid *PageViewer::pageGrid()
{
    return m_pageGrid;
}

void PageViewer::keyPressEvent(QKeyEvent *event)
{
    int k = event->key();
    if (k == Qt::Key_Delete)
    {
        event->accept();

        m_pageGrid->deleteSelectedPage();
        return;
    }

    QWidget::keyPressEvent(event);
}



/* ********************************************************************************* *
 *
 *
 * Page Grid
 *
 *
 * *********************************************************************************
 *
 * Grid Scheme for Double Page
 *
 *        Column 1       Column 2              Column 3       Column 4
 *     ------------------------------       ------------------------------
 *  R  | Group                      |       | Group                      |
 *  o  | ----------      ---------- | Group | ----------      ---------- |
 *  w  | | Cell   | Cell | Cell   | |  Gap  | | Cell   | Cell | Cell   | |
 *     | |        | Gap  |        | |       | |        | Gap  |        | |
 *  1  | ----------      ---------- |       | ----------      ---------- |
 *     ------------------------------       ------------------------------
 *                Group Gap                             Group Gap
 *     ------------------------------       ------------------------------
 *  R  | Group                      |       | Group                      |
 *  o  | ----------      ---------- | Group | ----------      ---------- |
 *  w  | | Cell   | Cell | Cell   | |  Gap  | | Cell   | Cell | Cell   | |
 *     | |        | Gap  |        | |       | |        | Gap  |        | |
 *  2  | ----------      ---------- |       | ----------      ---------- |
 *     ------------------------------       ------------------------------
 *
 * A group can have minimum 1 cell or maximum 4 cells
 *
 * ********************************************************************************* */



PageGrid::PageGrid(QWidget *parent)
    : QWidget{parent}
{
    m_pageList = new QList<PageCell*>();
    m_tileSize = 96;
    m_cellGap = 1;
    m_groupGap = 16;
    m_fontSize = 7;
    m_labelGap = 8;
    m_cellSize = QSize(m_tileSize, m_tileSize);
    m_pageOrientation = Qt::Vertical;
    m_colorSelection = QColor(255, 51, 51);
    m_pageOffset = 0;
    m_pageLayout = PageLayout::Single;
    m_cellsInGroup = 1; // single page
    m_selectedPage = -1;
    m_hoveredPage = -1;
    m_rectInsert = QRect();

    updateTileSize();
    setAcceptDrops(true);


    calculateSize();
    adjustSize();

}

/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

void PageGrid::setPageInGroup(int amount)
{
    m_cellsInGroup = amount;
}

void PageGrid::setTileSize(int size)
{
    // clamp size from 48 to 256)
    m_tileSize = qMin( qMax(size, 48), 256);
    updateTileSize();
    update();
}

int PageGrid::tileSize()
{
    return m_tileSize;
}

void PageGrid::setFontSize(int size)
{
    m_fontSize = size;
    updateTileSize();
    update();
}

int PageGrid::fontSize()
{
    return m_fontSize;
}

void PageGrid::setSelectionColor(QColor color)
{
    m_colorSelection = color;
    update();
}

QColor PageGrid::selectionColor()
{
    return m_colorSelection;
}

void PageGrid::setPageOrientation(Qt::Orientation orientation)
{
    m_pageOrientation = orientation;
    updateTileSize();
    update();
}

Qt::Orientation PageGrid::pageOrientation()
{
    return m_pageOrientation;
}

void PageGrid::setPageLayout(PageLayout layout)
{
    m_pageLayout = layout;

    switch(m_pageLayout){
    default:
    case PageLayout::Single:
        m_cellsInGroup = 1;
        break;
    case PageLayout::Double:
        m_cellsInGroup = 2;
        break;
    case PageLayout::ThreeFacing:
        m_cellsInGroup = 3;
        break;
    case PageLayout::FourFacing:
        m_cellsInGroup = 4;
        break;
    }

    update();
}

PageLayout PageGrid::pageLayout()
{
    return m_pageLayout;
}

void PageGrid::setPageOffset(int pageCount)
{
    m_pageOffset = pageCount;
    update();
}

int PageGrid::pageOffset()
{
    return m_pageOffset;
}

void PageGrid::setPageList(QList<PageCell *> *list)
{
    m_pageList = list;
    update();
}

QList<PageCell *> *PageGrid::pageList()
{
    return m_pageList;
}

int PageGrid::getPageId(int r, int c)
{
    int id = 0;

    if(r <= 0){
        id = c;
    }else{
        id = r * columns() + c;
    }

    return id - m_pageOffset;
}

PageCell *PageGrid::getPageItem(int pageIndex)
{
    if(pageCount() == 0 || pageIndex >= pageCount()){
        return nullptr;
    } else {
        // clamp id
        return m_pageList->at( qMin( qMax(pageIndex, 0), pageCount() -1 ) );
    }
}


int PageGrid::pageCount()
{
    return m_pageList->count();
}

void PageGrid::setSelectedPage(int pageID)
{
    m_selectedPage = clampPageID(pageID);
    update();
}


int PageGrid::selectedPage()
{
    return m_selectedPage;
}

void PageGrid::deleteSelectedPage()
{
    emit delPageRequest( clampPageID(m_selectedPage) );
}

/* ********************************************************************************* *
 *
 * Private Members
 *
 * ********************************************************************************* */

int PageGrid::columns()
{   
    return qFloor( (this->width() - m_groupGap) / groupWidth() * m_cellsInGroup );

}

int PageGrid::rows()
{
    // total page count + offset pages
    return qCeil((double)(pageCount() + m_pageOffset + 1) / (double)columns() );
}

int PageGrid::groupWidth()
{
    int allCells = m_cellSize.width() * m_cellsInGroup;
    int allCellGaps = m_cellGap * qMax(m_cellsInGroup - 1, 0);
    return m_groupGap + allCells + allCellGaps;
}

int PageGrid::columnAt(int c)
{
    if(pageCount() == 0) return -1;

    int groupCount = c / groupWidth(); // column of group
    int normalize = c - m_groupGap - groupWidth() * groupCount;
    int m_col = normalize / (m_cellSize.width() + m_cellGap) + m_cellsInGroup * groupCount;
    int m_columns = columns();

    return (m_col < m_columns) ? m_col : m_columns -1;
}

int PageGrid::rowAt(int r)
{
    if(pageCount() == 0) return -1;

    int gridHeight = m_groupGap + m_cellSize.height();
    int m_rows = rows();
    int m_row = r / gridHeight;

    return (m_row < m_rows) ? m_row : m_rows -1;
}

QPoint PageGrid::mapPosToCell(QPoint pos, bool *isInsert)
{
    int offset = m_groupGap;

    int col = columnAt(pos.x());
    int row = rowAt(pos.y());

    // return if there is no row or column
    if(col == -1 || row == -1) return QPoint();

    int groups = col / (double)m_cellsInGroup; // calculate amount full fitting groups
    int pages = col - groups * m_cellsInGroup; // calculate amount of pages of started group

    int x = offset + groups * groupWidth() + pages * m_cellSize.width() + pages * m_cellGap;
    int y = offset + row * (m_cellSize.height() + m_groupGap);

    // check if mouse is on "insert area"
    QRect insertArea(x,y, 8, m_cellSize.height());
    *isInsert = insertArea.contains(pos);

    return QPoint(x,y);
}

int PageGrid::clampPageID(int pageID, int offsetMax)
{
    return qMin( qMax(pageID, 0), pageCount() + offsetMax);
}


/* ********************************************************************************* *
 *
 * Methods
 *
 * ********************************************************************************* */

void PageGrid::updateSelectedPage(QPoint pos)
{       
    int col = columnAt(pos.x());
    int row = rowAt(pos.y());

    int id = getPageId(row, col);

    // check if page id is in range of an existing cell
    if(id > -1 && id < pageCount() ){
        int newSelectedPage = clampPageID( id );

        // repaint only if there is a change
        if(newSelectedPage != m_selectedPage){
            m_selectedPage = newSelectedPage;
            update();
        }
    }

}

void PageGrid::updateInsertSelector(QPoint pos)
{

    int col = columnAt(pos.x());
    int row = rowAt(pos.y());
    int id = getPageId(row, col);

    // return if position is out of range
    if(id < 0 || id > pageCount()) return;

    bool isInsert;

    QPoint mapPos = mapPosToCell(pos, &isInsert);

    int selectorWidth = 4;
    int offsetX = mapPos.x() - selectorWidth / 2 - qRound((double)m_cellGap / 2);

    // check if mouse is on "insert area"
    if(isInsert){
        m_rectInsert = QRect(offsetX, mapPos.y() - 4, selectorWidth, m_pageSize.height() + 8 );
        m_hoveredPage = -1;
    }else{
        m_rectInsert = QRect();
        m_hoveredPage = id;
    }

    update();

}

void PageGrid::updateTileSize()
{
    if(m_pageOrientation == Qt::Vertical){
        int longSide = m_tileSize - m_fontSize - m_labelGap;
        double shortSide = longSide / PAGERATIO;
        m_cellSize = QSize( shortSide, m_tileSize );
        m_pageSize = QSize( shortSide, longSide );
    }else{
        double shortSide = m_tileSize / PAGERATIO;
        m_cellSize = QSize( m_tileSize, shortSide + m_fontSize + m_labelGap );
        m_pageSize = QSize( m_tileSize, shortSide );
    }

}

void PageGrid::calculateSize()
{
    setMinimumHeight((rows()) * (m_cellSize.height() + m_groupGap) + m_groupGap);
    setMinimumWidth(groupWidth() + m_groupGap);

}

void PageGrid::clearUI()
{
    m_rectInsert = QRect();
    m_hoveredPage = -1;
    update();
}

void PageGrid::drawTile(QPainter &painter, QRect cellRect, PageCell *tile, bool selected, bool hovered)
{

    if(tile == nullptr) return;

    QFont font(this->font().family(), m_fontSize, QFont::Normal);

    int pageHeight = m_pageSize.height();
    int pageWidth = m_pageSize.width();

    QRect rectPage(cellRect.x(), cellRect.y(), pageWidth, pageHeight);

    painter.save();

    // Draw Page
    painter.drawPixmap(rectPage, tile->pagePreview, tile->pagePreview.rect());

    // Setup painter for text drawing
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.setFont(font);

    // Draw Page Number
    //painter.setPen(QPen(palette().windowText().color()));
    painter.setPen(QPen( Qt::white ));
    painter.drawText(cellRect, Qt::AlignHCenter|Qt::AlignBottom | Qt::TextWordWrap, QString::number(tile->pageNumber + 1));

    // Draw Page Name
    painter.setBackgroundMode(Qt::OpaqueMode);
    painter.setBackground(Qt::white);
    painter.setPen(QPen(Qt::black));
    painter.drawText(rectPage.adjusted(2,2,-2,-2), Qt::AlignTop | Qt::AlignLeft |Qt::TextWordWrap, tile->pageName);


    // selection
    if(selected){
        painter.setBrush(Qt::NoBrush);
        painter.setPen( QPen(m_colorSelection, 2) );
        painter.drawRect(rectPage);
    }

    // hover
    if(hovered){
        QColor colHover = palette().highlight().color();
        colHover.setAlphaF(0.5);
        painter.setBackgroundMode(Qt::TransparentMode);
        painter.setBrush(colHover);
        painter.setPen( Qt::NoPen );
        painter.drawRect(rectPage);
    }

    painter.restore();

}

/* ********************************************************************************* *
 *
 * Events
 *
 * ********************************************************************************* */

void PageGrid::paintEvent(QPaintEvent *event)
{

    int count = 0;
    int x = m_groupGap;
    int y = m_groupGap;
    int offset = 0;

    QPainter painter(this);

    // Draw background
    //painter.fillRect(rect(), palette().base());
    painter.fillRect(rect(), QColor(128,128,128));

    if(pageCount() == 0) return;

//    QElapsedTimer timer;
//    timer.start();

    // Draw pages
    for(int r = 0; r < rows(); r++){

        for(int c = 0; c < columns(); c++){

            if(count >= pageCount() + m_pageOffset) break;

            QRect rectCell(x,y, m_cellSize.width(), m_cellSize.height() );

            if(count >= m_pageOffset){
                int id = count - m_pageOffset;
                PageCell * cell = getPageItem(id);
                drawTile(painter, rectCell, cell, (id == m_selectedPage) ? true : false, (id == m_hoveredPage) ? true : false);
            }

            // add x-space
            offset = ((c + 1) % m_cellsInGroup) == 0 ? m_groupGap : m_cellGap;

            x += m_cellSize.width() + offset;
            count++;
        }

        y += m_cellSize.height() + m_groupGap;
        x = m_groupGap;
    }


    // Draw insert marker
    painter.fillRect(m_rectInsert, palette().highlight());

    painter.end();

   // qDebug() << "Render Time Page Grid:" << timer.elapsed() << "milliseconds";

}


void PageGrid::resizeEvent(QResizeEvent *event)
{
    if (event->oldSize() != event->size()){

        calculateSize();

    }
    QWidget::resizeEvent(event);
}

void PageGrid::dropEvent(QDropEvent *event)
{   

    if (!event->mimeData()->hasFormat("page/magic"))
        return;

    QPoint dropEventPos = event->position().toPoint();
    event->setDropAction(Qt::MoveAction);
    event->accept();
    // HACK to prevent strange Qt4 cursor behaviour after dropping. It's examined by Trolltech now - PV.
    // It's the one and only reason why to include QApplication here.
    // But sadly this destroys our normal Cursors
    // Fixed at least in Qt-4.4.2
  //  QApplication::restoreOverrideCursor();
    clearUI();

    QString tmp;
    QString str = event->mimeData()->text();

    // external drop
    if (str.startsWith("1")){

        int a = rowAt(dropEventPos.y());
        int b = columnAt(dropEventPos.x());
        int p;
        tmp = str.remove(0,1);

        if ((a == -1) || (b == -1))
            return;

        if (a == rows() - 1)
        {
            emit NewPage(pageCount(), tmp);
            return;
        }

        p = getPageId(a, b);

        if (columns() == 1)
        {
            emit NewPage(p, tmp);
            return;
        }

        bool isInsert = false;
        mapPosToCell(dropEventPos, &isInsert);

        if(isInsert){
            emit NewPage(p, tmp);
        }else{
            emit UseTemp(p, tmp);
        }

        return;

    }

    // internal drop
    if (str.startsWith("2")){

        int st = str.indexOf(" ");
        int en = str.indexOf(" ", st + 1);
        tmp = str.mid(en + 1);
        int dr = QStringView(str).sliced(st, en - st).toInt();
        int r = rowAt(dropEventPos.y());
        int c = columnAt(dropEventPos.x());

        if ((r == -1) || (c == -1))
            return;

        bool isInsert = false;
        mapPosToCell(dropEventPos, &isInsert);


        // clamp ID from 0 to max+1
        int p = clampPageID(getPageId(r, c), 0); //qMin( qMax(getPageId(r, c), 0), pageCount());

        if(isInsert){
            emit movePage(dr, p);
        }else{
            emit UseTemp(p, tmp);
        }

        return;

    }

}

void PageGrid::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("page/magic"))
        event->acceptProposedAction();
}

void PageGrid::dragLeaveEvent(QDragLeaveEvent *event)
{   
    clearUI();
}

void PageGrid::dragMoveEvent(QDragMoveEvent *event)
{
    if (!event->mimeData()->hasFormat("page/magic"))
        return;

    event->acceptProposedAction();
    // clearPix();

    QPoint dragEventPos = event->position().toPoint();
    int row = rowAt(dragEventPos.y());
    int col = columnAt(dragEventPos.x());
    if ((row == -1) || (col == -1))
        return;

    updateInsertSelector(dragEventPos);

}

void PageGrid::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
    m_mousePressed = false;

    QPoint mouseEventPos = event->position().toPoint();

    if(pageCount() > 0){

        updateSelectedPage(mouseEventPos);

        int row = rowAt(mouseEventPos.y());
        int col = columnAt(mouseEventPos.x());
        int pageID = getPageId(row, col);

        if(pageID > -1 && pageID < pageCount() ){
            // TODO: it would be better to send selected page ID directly (m_selectedPage)
            emit Click(row, col, event->button());
        }
    }

    QWidget::mouseReleaseEvent(event);
}

void PageGrid::mousePressEvent(QMouseEvent *event)
{
    event->accept();
    m_mousePos = event->position().toPoint();
    m_mousePressed = true;

    QWidget::mousePressEvent(event);
}

void PageGrid::mouseMoveEvent(QMouseEvent *event)
{

    QPoint mouseEventPos = event->position().toPoint();
    if ((m_mousePressed) && ((m_mousePos - mouseEventPos).manhattanLength() > 4))
    {
        m_mousePressed = false;
        int a = rowAt(mouseEventPos.y());
        int b = columnAt(mouseEventPos.x());
        if ((a != -1) && (b != -1))
        {
            PageCell* ite = getPageItem(getPageId(a, b));
            if (ite != nullptr)
            {

                //PageItem* it = (PageItem*)ite;
                QString str(ite->pageName);

                int p = ite->pageNumber;//getPage(a, b);
                QString tmp;
                QMimeData *mimeData = new QMimeData;
                mimeData->setData("page/magic", "2 " + tmp.setNum(p).toLocal8Bit() + " " + str.toLocal8Bit());
                mimeData->setText("2 " + tmp.setNum(p) + " " + str);
                QDrag *dr = new QDrag(this);
                dr->setMimeData(mimeData);
                const QPixmap& pm = IconManager::instance().pixmap("page-drag");
                dr->setPixmap(pm);
                //	dr->setDragCursor(pm, Qt::CopyAction);
                //	dr->setDragCursor(pm, Qt::MoveAction);
                dr->exec(Qt::CopyAction | Qt::MoveAction);
                //QApplication::setOverrideCursor(Qt::ArrowCursor);

            }
        }
    }
    QWidget::mouseMoveEvent(event);
}


