/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/

#include <QApplication>
//#include <QBitmap>
//#include <QCursor>
#include <QDrag>
//#include <QEvent>
//#include <QHeaderView>
//#include <QLabel>
//#include <QList>
#include <QMenu>
#include <QMimeData>
//#include <QMessageBox>
//#include <QPainter>
//#include <QStringView>

#include <QMouseEvent>

#include "icon_manager.h"
#include "pagelist.h"


/* ********************************************************************************* *
 *
 * Master Page List
 *
 * ********************************************************************************* */
PageList::PageList(QWidget* parent) : QListWidget(parent)
{
    setAcceptDrops(true);
}

void PageList::mouseReleaseEvent(QMouseEvent *m)
{
    m_mousePressed = false;
    if (m->button() == Qt::RightButton)
    {
        QMenu *pmen = new QMenu();
//		qApp->changeOverrideCursor(QCursor(Qt::ArrowCursor));
        QAction *px = pmen->addAction( tr("Show Page Previews"), this, SLOT(toggleThumbnail()));
        px->setCheckable(true);
        if (m_thumb)
            px->setChecked(true);
        pmen->exec(QCursor::pos());
        delete pmen;
    }
    QListWidget::mouseReleaseEvent(m);
}

void PageList::toggleThumbnail()
{
    m_thumb = !m_thumb;
    emit thumbnailChanged();
}

void PageList::mousePressEvent(QMouseEvent* e)
{
    e->accept();
    m_currItem = nullptr;
    QListWidgetItem *i = itemAt(e->position().toPoint());
    if (i)
    {
        m_currItem = i;
        m_mousePos = e->position().toPoint();
        m_mousePressed = true;
    }
    QListWidget::mousePressEvent(e);
}

void PageList::mouseMoveEvent(QMouseEvent* e)
{
    if ((m_mousePressed) && ((m_mousePos - e->pos()).manhattanLength() > 4))
    {
        m_mousePressed = false;
        QListWidgetItem *item = itemAt(m_mousePos);
        if (!item)
            return;
        QMimeData *mimeData = new QMimeData;
        QString pageName = item->data(Qt::UserRole).toString();
        mimeData->setData("page/magic", "1" + pageName.toLocal8Bit());
        mimeData->setText("1" + pageName);
        QDrag *dr = new QDrag(this);
        dr->setMimeData(mimeData);
        const QPixmap& pm = IconManager::instance().pixmap("page-drag");
        dr->setPixmap(pm);
    //	dr->setDragCursor(pm, Qt::CopyAction);
    //	dr->setDragCursor(pm, Qt::MoveAction);
        dr->exec(Qt::CopyAction | Qt::MoveAction);
       // QApplication::setOverrideCursor(Qt::ArrowCursor);
    }
}

void PageList::keyPressEvent(QKeyEvent * e)
{
    int k = e->key();
    if (k == Qt::Key_Delete)
    {
        if (currentItem())
        {
            e->accept();
            emit delMasterRequest(currentItem()->text());
            return;
        }
    }

    QListWidget::keyPressEvent(e);
}
