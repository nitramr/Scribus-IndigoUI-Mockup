#ifndef COMBOBOXFIRSTPAGE_H
#define COMBOBOXFIRSTPAGE_H

#include "enums.h"
#include <QComboBox>
#include <QWidget>

class ComboBoxFirstPage : public QComboBox
{
    Q_OBJECT
public:
    ComboBoxFirstPage(QWidget *parent = nullptr);

    void setPageLayout(PageLayout pageLayout);
    PageLayout pageLayout();

private:
    PageLayout m_pageLayout;
};

#endif // COMBOBOXFIRSTPAGE_H
