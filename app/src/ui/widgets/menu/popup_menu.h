#ifndef POPUP_MENU_H
#define POPUP_MENU_H

#include <QMenu>
#include <QWidgetAction>

class PopupMenu : public QMenu
{

    Q_CLASSINFO("Version", "1.0.0")

public:
    PopupMenu(QWidget*contentWidget);
protected:
	bool eventFilter(QObject *obj, QEvent *event);

   void paintEvent(QPaintEvent *event);
   QPainterPath shape();

};

#endif // POPUP_MENU_H
