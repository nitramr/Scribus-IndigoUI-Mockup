#ifndef PAGEVIEWER_H
#define PAGEVIEWER_H

#include "enums.h"
#include <QWidget>
#include <QPixmapCache>
#include <QScrollArea>

class PageCell
{
    friend class PanelPages;
    friend class PageGrid;

public:
    PageCell(const QString& text, uint pgnr, const QPixmap& pix);
    // ~PageCell() {};

    const QString& getPageName();
    uint pageNumber;
    QPixmap pagePreview;

protected:
    QString pageName;
};



class PageGrid : public QWidget
{
    Q_OBJECT
public:
    explicit PageGrid(QWidget *parent = nullptr);

    void setPageInGroup(int amount);

    void setTileSize(int size);
    int tileSize();

    void setFontSize(int size);
    int fontSize();

    void setSelectionColor(QColor color);
    QColor selectionColor();

    void setPageOrientation(Qt::Orientation orientation);
    Qt::Orientation pageOrientation();

    void setPageLayout(PageLayout layout);
    PageLayout pageLayout();

    void setPageOffset(int pageCount);
    int pageOffset();

    void setPageList(QList<PageCell*> *list);
    QList<PageCell*> * pageList();

    int getPageId(int r, int c);
    PageCell* getPageItem(int pageIndex);

    int pageCount();

    void setSelectedPage(int pageID);
    int selectedPage();

    void deleteSelectedPage();

private:
    QList<PageCell*> * m_pageList;
    QSize m_cellSize;
    QSize m_pageSize;
    int m_tileSize;
    int m_cellGap;
    int m_groupGap;    
    int m_fontSize;
    int m_labelGap;    
    QRect m_rectInsert;
    Qt::Orientation m_pageOrientation;
    QColor m_colorSelection;
    int m_selectedPage;
    int m_hoveredPage;

    PageLayout m_pageLayout;
    int m_cellsInGroup;
    int m_pageOffset;

    int columns();
    int rows();

    int groupWidth();

    int columnAt(int c);
    int rowAt(int r);

    QPoint mapPosToCell(QPoint pos, bool *isInsert);

    int clampPageID(int pageID, int offsetMax = -1);

    void updateSelectedPage(QPoint pos);
    void updateInsertSelector(QPoint pos);
    void updateTileSize();
    void calculateSize();

    void clearUI();
    void drawTile(QPainter &painter, QRect cellRect, PageCell * tile, bool selected, bool hovered);


protected:

    QPoint m_mousePos;
    bool m_mousePressed {false};

    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

    virtual void dropEvent(QDropEvent * event);
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dragLeaveEvent(QDragLeaveEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);

signals:
    void UseTemp(int, QString);
    void NewPage(int, QString);
    void movePage(int, int);
    void Click(int, int, int);
    void delPageRequest(int);
};



class PageViewer : public QWidget
{
    friend class PageGrid;

public:
    PageViewer(QWidget *parent = nullptr);
    ~PageViewer() {};

    PageGrid *pageGrid();


protected:
    PageGrid *m_pageGrid;

    virtual void keyPressEvent(QKeyEvent* event);

};

#endif // PAGEVIEWER_H
