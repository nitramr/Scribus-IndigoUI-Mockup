/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#ifndef BUTTONAUTOFORMS_H
#define BUTTONAUTOFORMS_H

#include <QMenu>
#include <QPixmap>
#include <QToolButton>
#include <QWidgetAction>

#include "scribusapi.h"
class AutoFormsMenu;

class SCRIBUS_API AutoFormsButton : public QToolButton
{
    Q_OBJECT

public:
    AutoFormsButton( QWidget* parent );
    ~AutoFormsButton() {};

    QPixmap getIconPixmap(int nr);

public slots:
    void selForm(int a);
    void iconSetChange();

signals:
    void FormSel(int, int, qreal *);

protected:
    AutoFormsMenu* buttonGroup1 { nullptr };
};

#endif // BUTTONAUTOFORMS_H
