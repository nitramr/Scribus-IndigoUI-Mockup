#ifndef PANEL_PAGES_H
#define PANEL_PAGES_H

#include "dialog_duplicatepage.h"
#include "dialog_importpage.h"
#include "dialog_importparentpage.h"
#include "dialog_newpage.h"
#include "dialog_movepage.h"
#include "dialog_newparentpage.h"
#include "pagelist.h"
#include <QWidget>

namespace Ui {
class PanelPages;
}

class PanelPages : public QWidget
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

     DialogNewPage          * dialogInsertPage;
     DialogDuplicatePage    * dialogDuplicatePage;
     DialogMovePage         * dialogMovePage;
     DialogNewParentPage    * dialogNewParentPage;
     DialogImportPage       * dialogImportPage;
     DialogImportParentPage * dialogImportParentPage;

//    QPixmap pix;

    void setup();
    void connectSlots();

    void rebuildMasters();


};

#endif // PANEL_PAGES_H
