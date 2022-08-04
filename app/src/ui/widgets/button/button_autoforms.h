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
class MenuAutoForms;

class SCRIBUS_API ButtonAutoForms : public QToolButton
{
    Q_OBJECT

public:
    ButtonAutoForms( QWidget* parent );
    ~ButtonAutoForms() {};

    QPixmap getIconPixmap(int nr);

public slots:
    void selForm(int a);
    void iconSetChange();

signals:
    void FormSel(int, int, qreal *);

protected:
    MenuAutoForms* buttonGroup1 { nullptr };
};

#endif // BUTTONAUTOFORMS_H
