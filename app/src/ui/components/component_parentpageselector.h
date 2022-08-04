#ifndef COMPONENT_PARENTPAGESELECTOR_H
#define COMPONENT_PARENTPAGESELECTOR_H

#include "enums.h"
#include <QComboBox>
#include <QWidget>

namespace Ui {
class ComponentParentPageSelector;
}

class ComponentParentPageSelector : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentParentPageSelector(QWidget *parent = nullptr);
    ~ComponentParentPageSelector();

    void setPageLayout(PageLayout pageLayout);
    PageLayout pageLayout();

    QComboBox * parentPage();
    QComboBox * left();
    QComboBox * middleLeft();
    QComboBox * middle();
    QComboBox * middleRight();
    QComboBox * Right();

private:
    Ui::ComponentParentPageSelector *ui;
    PageLayout m_pageLayout;

    void setup();

};

#endif // COMPONENT_PARENTPAGESELECTOR_H
