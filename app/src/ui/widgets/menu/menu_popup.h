#ifndef MENU_POPUP_H
#define MENU_POPUP_H

#include <QMenu>
#include <QWidgetAction>

class MenuPopup : public QMenu
{

    Q_CLASSINFO("Version", "1.0.0")

public:
    MenuPopup(QWidget*contentWidget);
protected:
	bool eventFilter(QObject *obj, QEvent *event);

   void paintEvent(QPaintEvent *event);
   QPainterPath shape();

};

#endif // MENU_POPUP_H
