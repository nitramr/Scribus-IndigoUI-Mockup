#ifndef DOCK_DOCUMENTBASE_H
#define DOCK_DOCUMENTBASE_H

#include <DockWidget.h>
#include <QMenu>
#include <QToolButton>
//#include "managepageproperties_dialog.h"
#include "dummydocument.h"
#include "panel_content.h"


class DockDocumentBase : public ads::CDockWidget
{

    Q_OBJECT

public:
    DockDocumentBase(const QString &title, QWidget *parent = 0);

private:

    void setup();
    void connectSlots();

    void dummyContent();


private slots:
    void changeContentMode(int id);

private:

    // Dummy
    DummyDocument * dummyDoc;
    QToolButton * buttonText;
    QToolButton * buttonImage;
    QToolButton * buttonTable;
    QButtonGroup * buttonGroupContentToggle;

signals:
    void changedContentMode(PanelContent::ContentMode mode);


};

#endif // DOCK_DOCUMENTBASE_H
