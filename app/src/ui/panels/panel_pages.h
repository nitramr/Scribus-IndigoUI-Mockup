#ifndef PANEL_PAGES_H
#define PANEL_PAGES_H

#include "duplicatepage_dialog.h"
#include "importpage_dialog.h"
#include "importparentpage_dialog.h"
#include "newpage_dialog.h"
#include "movepage_dialog.h"
#include "newparentpage_dialog.h"
#include "page_list/page_list.h"
#include "section_container/section_container.h"
#include "panel.h"
#include <QWidget>

namespace Ui {
class PanelPages;
}

class PanelPages : public Panel
{
    Q_OBJECT

public:
    explicit PanelPages(QWidget *parent = nullptr);
    ~PanelPages();

public slots:


private slots:
    void useTemplate(int pageId, QString parentPage);
    void newPage(int pageId, QString parentPage);
    void movePage(int oldId, int newId);
    void click(int row, int column, int button);
    void delPageRequest(int pageId);
    void delParentRequest(QString parentPage);

    void showAddPageDialog();
    void showDuplicatePageDialog();
    void showMovePageDialog();
    void showImportPageDialog();

    void showNewParentPageDialog();
    void showImportParentPageDialog();


    void changeDocumentLayout();
    void changeFirstPage();

private:
    Ui::PanelPages *ui;

     NewPageDialog          * dialogInsertPage;
     DuplicatePageDialog    * dialogDuplicatePage;
     MovePageDialog         * dialogMovePage;
     NewParentPageDialog    * dialogNewParentPage;
     ImportPageDialog       * dialogImportPage;
     ImportParentPageDialog * dialogImportParentPage;

//    QPixmap pix;

    void setup();
    void connectSlots();

    void rebuildMasters();
    void updateLayout(bool isCollapsed);


};

#endif // PANEL_PAGES_H
