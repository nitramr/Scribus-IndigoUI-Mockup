/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#include "colorlistview.h"

#include <cstdlib>
//#include <QBitmap>
//#include <QCursor>
//#include <QEvent>
#include <QHelpEvent>
#include <QMenu>
//#include <QPainter>
//#include <QPersistentModelIndex>
//#include <QPixmap>
//#include <QSignalBlocker>
//#include <QToolTip>

#include "colorlistmodel.h"
#include "commonstrings.h"
#include "iconmanager.h"
//#include "scribusdoc.h"

#include "colorlistitemdelegate.h"


int ColorListView::initialized;
int ColorListView::sortRule;

/* ********************************************************************************* *
 *
 * Constructor
 *
 * ********************************************************************************* */

ColorListView::ColorListView(QWidget * parent)
    : ColorListView(ColorListView::widePixmap, parent)
{
//    if (initialized != 12345)
//        sortRule = 0;
//    initialized = 12345;
//    QListView::setModel(new ColorListModel(this));
//    setPixmapType(ColorListView::widePixmap);

//    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(emitItemClicked(QModelIndex)));
//    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(emitItemDoubleClicked(QModelIndex)));
//    connect(this->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(emitCurrentChanged(QModelIndex,QModelIndex)));
//    connect(this->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SIGNAL(itemSelectionChanged()));
//    connect(this, SIGNAL(contextMenuRequested()), this, SLOT(slotRightClick()));
}

ColorListView::ColorListView(ColorListView::PixmapType type, QWidget * parent)
    : QListView(parent)
{
    cList = nullptr;
    if (initialized != 12345)
        sortRule = 0;
    initialized = 12345;
    QListView::setModel(new ColorListModel(this));
    setPixmapType(type);

    //connect(ScQApp, SIGNAL(iconSetChanged()), this, SLOT(iconSetChange()));

    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(emitItemClicked(QModelIndex)));
    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(emitItemDoubleClicked(QModelIndex)));
    connect(this->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(emitCurrentChanged(QModelIndex,QModelIndex)));
    connect(this->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SIGNAL(itemSelectionChanged()));
    connect(this, SIGNAL(contextMenuRequested()), this, SLOT(slotRightClick()));
}

ColorListView::~ColorListView()
{
    if (itemDelegate())
        delete itemDelegate();
    clear();
}




/* ********************************************************************************* *
 *
 * Members
 *
 * ********************************************************************************* */

QString ColorListView::currentColor() const
{
    if (currentRow() >= 0)
    {
        QAbstractItemModel* itemModel = model();
        return itemModel->data(currentIndex(), Qt::DisplayRole).toString();
    }
    return CommonStrings::tr_NoneColor;
}


int ColorListView::currentRow() const
{
    return currentIndex().row();
}


int ColorListView::count() const
{
    return this->model()->rowCount();
}


QVariant ColorListView::data(int row, int role) const
{
    QModelIndex index = model()->index(row, 0);
    return model()->data(index, role);
}


QStringList ColorListView::findColors(const QString &name, Qt::MatchFlags flags) const
{
    QStringList foundColors;
    QAbstractItemModel* currentModel = model();

    QModelIndex firstIndex = currentModel->index(0, 0, QModelIndex());
    QModelIndexList indexes = currentModel->match(firstIndex, Qt::DisplayRole, name, -1, flags);
    for (int i = 0; i < indexes.count(); ++i)
    {
        QModelIndex modelIndex = indexes.at(i);
        QVariant modelData = currentModel->data(modelIndex, Qt::DisplayRole);
        foundColors.append(modelData.toString());
    }

    return foundColors;
}


bool ColorListView::hasSelection() const
{
    return this->selectionModel()->hasSelection();
}


bool ColorListView::isNoneColorShown() const
{
    ColorListModel* colorListModel = qobject_cast<ColorListModel*>(model());
    if (colorListModel)
        return colorListModel->isNoneColorShown();
    return false;
}

int ColorListView::row(const QString& colorName)
{
    QAbstractItemModel* currentModel = model();

    QModelIndex firstIndex = currentModel->index(0, 0, QModelIndex());
    QModelIndexList indexes = currentModel->match(firstIndex, Qt::DisplayRole, colorName, -1, Qt::MatchExactly);
    if (indexes.count() > 0)
    {
        const QModelIndex& first = indexes.at(0);
        return first.row();
    }
    return -1;
}


QString ColorListView::text(int row) const
{
    QVariant varText = data(row, Qt::DisplayRole);
    return varText.toString();
}

/* ********************************************************************************* *
 *
 * Functions
 *
 * ********************************************************************************* */

void ColorListView::updateBox(ColorList& list)
{
    bool showNoneColor = false;

    clear();
    reset();

    ColorListModel* colorModel = qobject_cast<ColorListModel*>(this->model());
    if (colorModel)
        showNoneColor = colorModel->isNoneColorShown();
    setColors(list, showNoneColor);
}

void ColorListView::insertItem(int row, const ScColor& color, const QString& colorName)
{
    ColorListModel* colorListModel = qobject_cast<ColorListModel*>(model());
    if (!colorListModel)
        return;

//    ScribusDoc* doc = nullptr;
//    if (cList)
//        doc = cList->document();

    ColorPixmapValue value(color, colorName);
    colorListModel->insert(row, value);
}

void ColorListView::removeItem(int i)
{
    // None color item cannot be removed
    if (isNoneColorShown() && (i == 0))
        return;

    model()->removeRow(i);
}

void ColorListView::setColors(ColorList& list, bool insertNone)
{
    ColorList::Iterator it;

    ColorListModel* colorModel = qobject_cast<ColorListModel*>(this->model());
    if (!colorModel)
        return;

    cList = &list;

    colorModel->setColorList(list, insertNone);
}


void ColorListView::setCurrentColor(QString colorName)
{
    if (colorName == CommonStrings::None)
        colorName = CommonStrings::tr_NoneColor;

    QModelIndex firstIndex = model()->index(0, 0, QModelIndex());
    QModelIndexList indexes = this->model()->match(firstIndex, Qt::DisplayRole, colorName, -1, Qt::MatchExactly);
    if (indexes.count() > 0)
        this->selectionModel()->setCurrentIndex(indexes[0], QItemSelectionModel::ClearAndSelect);
}



void ColorListView::setCurrentRow(int row)
{
    QModelIndex index = this->model()->index(row, 0);
    selectionModel()->setCurrentIndex(index, QItemSelectionModel::ClearAndSelect);
}


void ColorListView::setPixmapType(ColorListView::PixmapType type)
{
    if (type == ColorListView::fancyPixmap)
    {
        QAbstractItemDelegate* oldDelegate = itemDelegate();
        ColorFancyItemDelegate* colorDelegate = dynamic_cast<ColorFancyItemDelegate*>(oldDelegate);
        if (!colorDelegate)
        {
            setItemDelegate(new ColorFancyItemDelegate());
            delete oldDelegate;
            m_type = type;
        }
    }
    else if (type == ColorListView::widePixmap)
    {
        QAbstractItemDelegate* oldDelegate = itemDelegate();
        ColorWideItemDelegate* colorDelegate = dynamic_cast<ColorWideItemDelegate*>(oldDelegate);
        if (!colorDelegate)
        {
            setItemDelegate(new ColorWideItemDelegate());
            delete oldDelegate;
            m_type = type;
        }
    }
    else if (type == ColorListView::smallPixmap)
    {
        QAbstractItemDelegate* oldDelegate = itemDelegate();
        ColorSmallItemDelegate* colorDelegate = dynamic_cast<ColorSmallItemDelegate*>(oldDelegate);
        if (!colorDelegate)
        {
            setItemDelegate(new ColorSmallItemDelegate());
            delete oldDelegate;
            m_type = type;
        }
    }
}


void ColorListView::setShowNoneColor(bool showNone)
{
    ColorListModel* colorListModel = qobject_cast<ColorListModel*>(model());
    if (colorListModel)
        colorListModel->setShowNoneColor(showNone);
}

/* ********************************************************************************* *
 *
 * Events
 *
 * ********************************************************************************* */

void ColorListView::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange)
    {
        languageChange();
        return;
    }
    QListView::changeEvent(e);
}

bool ColorListView::viewportEvent(QEvent *event)
{
    if (event != nullptr)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::RightButton)
                return true;
        }
        else if (event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::RightButton)
            {
                emit contextMenuRequested();
                return true;
            }
        }
    }
    return QListView::viewportEvent(event);
}

/* ********************************************************************************* *
 *
 * Public Slots
 *
 * ********************************************************************************* */

void ColorListView::clear()
{
    QAbstractItemModel* itemModel = model();
    itemModel->removeRows(0, itemModel->rowCount());
}

/* ********************************************************************************* *
 *
 * Protected Slots
 *
 * ********************************************************************************* */

void ColorListView::emitCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    QPersistentModelIndex persistentCurrent = current;

    QString text = model()->data(current, Qt::DisplayRole).toString();
    emit currentTextChanged(text);
    emit currentRowChanged(persistentCurrent.row());
}

void ColorListView::emitItemClicked(const QModelIndex &current)
{
    QPersistentModelIndex persistentCurrent = current;
    emit itemClicked(persistentCurrent.row());
}

void ColorListView::emitItemDoubleClicked(const QModelIndex &current)
{
    QPersistentModelIndex persistentCurrent = current;
    emit itemDoubleClicked(persistentCurrent.row());
}

void ColorListView::iconSetChange()
{
    if (m_type == ColorListView::fancyPixmap)
    {
        QAbstractItemDelegate* curDelegate = itemDelegate();
        ColorFancyItemDelegate* colorDelegate = dynamic_cast<ColorFancyItemDelegate*>(curDelegate);
        if (colorDelegate)
        {
            colorDelegate->iconSetChange();
            this->update();
        }
    }
}

void ColorListView::languageChange()
{
    // Not needed anymore normally: on language change a paintEvent is sent to widget
    // and model will return the new translated string for None color
    /*if (this->count() > 0)
    {
        QModelIndexList result;
        QModelIndex start = model()->index(0, 0, this->rootIndex());
        result =  model()->match(start, Qt::UserRole, CommonStrings::None, 1, Qt::MatchExactly | Qt::MatchCaseSensitive);
        if (result.isEmpty())
            return;
        int index = result.first().row();
        QListWidgetItem* item = this->item(index);
        item->setText(CommonStrings::tr_NoneColor);
    }*/
}

/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */


void ColorListView::slotRightClick()
{
    QSignalBlocker sigBlocker(this);
    QString currentSel = currentColor();
    if (currentSel.isEmpty())
        return;

    QMenu *pmen = new QMenu();
    pmen->addAction( tr("Sort by Name"));
    pmen->addAction( tr("Sort by Color"));
    pmen->addAction( tr("Sort by Type"));
    sortRule = pmen->actions().indexOf(pmen->exec(QCursor::pos()));
    delete pmen;

    ColorListModel* colorListModel = qobject_cast<ColorListModel*>(model());
    if (!colorListModel)
        return;

    if (sortRule == 0)
        colorListModel->setSortRule(ColorListModel::SortByName);
    else if (sortRule == 1)
        colorListModel->setSortRule(ColorListModel::SortByValues);
    else if (sortRule == 2)
        colorListModel->setSortRule(ColorListModel::SortByType);

    if (!currentSel.isEmpty())
        setCurrentColor(currentSel);
}
