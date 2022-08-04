/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#ifndef PAGELIST_H
#define PAGELIST_H

//#include <QCheckBox>
//#include <QDialog>
//#include <QDragEnterEvent>
//#include <QDragLeaveEvent>
//#include <QDragMoveEvent>
//#include <QDropEvent>
//#include <QHBoxLayout>
//#include <QImage>
//#include <QKeyEvent>
//#include <QLabel>
//#include <QLayout>
#include <QListWidget>
//#include <QMouseEvent>
//#include <QPixmap>
//#include <QPushButton>
//#include <QSplitter>
//#include <QTableWidget>
//#include <QTableWidgetItem>
//#include <QToolTip>
//#include <QVBoxLayout>

class QEvent;

#include "scribusapi.h"

/* ********************************************************************************* *
 *
 * Parent Page list
 *
 * ********************************************************************************* */

class PageList : public QListWidget
{
    friend class PanelPages;
//    friend class PagePalette_Pages;

    Q_OBJECT

public:
    PageList(QWidget* parent);
    ~PageList() {};

private slots:
    void toggleThumbnail();

signals:
    //! Emitted when user requests/disables the thumbnais for master pages.
    void thumbnailChanged();
    void delMasterRequest(QString);

protected:
    void mouseReleaseEvent(QMouseEvent *m);
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    virtual void keyPressEvent(QKeyEvent* e);

    QListWidgetItem *m_currItem {nullptr};
    QPoint m_mousePos;
    bool m_mousePressed {false};
    bool m_thumb {false};

};




#endif
