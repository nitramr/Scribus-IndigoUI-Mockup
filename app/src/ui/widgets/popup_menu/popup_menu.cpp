/*************************************************************************************

   Draftoola - UI and UX prototyping tool for designing static and animated layouts.

   Copyright (C) 2019 Martin Reininger <nitramr>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

**************************************************************************************/

#include "popup_menu.h"
#include <QEvent>
#include <QBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>

/*!
 * \brief [CTR]
 * \param widget
 */
PopupMenu::PopupMenu(QWidget *contentWidget)
{
    if(contentWidget == nullptr) contentWidget = new QWidget();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(contentWidget);
    layout->setContentsMargins(1,1,1,1);

    QWidget *panel = new QWidget();
    panel->setMinimumSize(contentWidget->size());
    panel->setLayout(layout);

    QWidgetAction * action = new QWidgetAction(this);
    action->setDefaultWidget(panel);

    contentWidget->installEventFilter(this);
//    contentWidget->setWindowFlags(Qt::Widget);

    addAction(action);    
//    setAutoFillBackground(false);
//    setWindowFlags(this->windowFlags() |/* Qt::FramelessWindowHint |*/ Qt::ToolTip);
//    setAttribute(Qt::WA_TranslucentBackground);

//    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
//    effect->setBlurRadius(5);
    //contentWidget->setGraphicsEffect(effect);


}

bool PopupMenu::eventFilter(QObject *obj, QEvent *event)
{

	// prevent that menu is close by interact with the background
	if (event->type() == QEvent::MouseButtonPress ||
			event->type() == QEvent::MouseButtonDblClick ||
			event->type() == QEvent::MouseMove) {

		return true;
	}

		return QObject::eventFilter(obj, event);

}

void PopupMenu::paintEvent(QPaintEvent *event)
{
//    QMenu::paintEvent(event);

    QPainter painter(this);
    painter.fillRect(rect(), Qt::transparent);

    painter.setBrush( QBrush(palette().color(QPalette::Window)) );
    painter.setPen( QPen(palette().color(QPalette::Mid)) );
//    painter.setPen( Qt::NoPen) ;

    painter.drawRect(this->rect().adjusted(0,0,-1,-1));

  //  painter.drawPath(shape());

}

QPainterPath PopupMenu::shape()
{
    int pHeight = 20;
    int pWidth = 20;
    int w = width() -1;
    int h = height() -1;

    QPainterPath pp;
    pp.moveTo(1,pHeight); // top left
    pp.lineTo(w/2 - pWidth/2, pHeight);
    pp.lineTo(w/2, 1);
    pp.lineTo(w/2 + pWidth/2, pHeight);
    pp.lineTo(w,pHeight); // top right
    pp.lineTo(w, h); // bottom right
    pp.lineTo(1, h); // bottom left
    pp.closeSubpath();

    return pp;
}
