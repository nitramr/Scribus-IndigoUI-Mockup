#include "trashbin_widget.h"
#include <QEvent>
#include <QMimeData>
#include <QDragEnterEvent>
#include "icon_manager.h"

/* ********************************************************************************* *
 *
 * Trash Bin
 *
 * ********************************************************************************* */
TrashBinWidget::TrashBinWidget(QWidget * parent) : QLabel(parent)
{

    setScaledContents(false);
    setAcceptDrops(true);
    iconSetChange();

    // connect(ScQApp, SIGNAL(iconSetChanged()), this, SLOT(iconSetChange()));
}

void TrashBinWidget::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasFormat("page/magic"))
    {
        e->accept();
        setPixmap(Open);
    }
}

void TrashBinWidget::dragLeaveEvent(QDragLeaveEvent *)
{
    setPixmap(Normal);
}

void TrashBinWidget::dropEvent(QDropEvent * e)
{
    setPixmap(Normal);
    QString str, tmp;
    if (e->mimeData()->hasFormat("page/magic"))
    {
        e->accept();
        str = e->mimeData()->text();

        if (str.startsWith("2"))
        {
            int st = str.indexOf(" ");
            int en = str.indexOf(" ", st + 1);
            emit delPageRequest(QStringView(str).sliced(st, en - st).toInt());
        }

        if (str.startsWith("1"))
        {
            tmp = str.remove(0,1);
            emit delMasterRequest(tmp);
        }
    }
}

void TrashBinWidget::iconSetChange()
{
    QSize size(20,20);

    QPixmap n = IconManager::instance().pixmap("page-delete-close");
    if(!n.isNull()) Normal = n.scaled(size, Qt::KeepAspectRatio);

    QPixmap o = IconManager::instance().pixmap("page-delete-open");
    if(!o.isNull()) Open = n.scaled(size, Qt::KeepAspectRatio);

    setPixmap(Normal);
}

