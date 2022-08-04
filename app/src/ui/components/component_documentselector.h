#ifndef COMPONENT_DOCUMENTSELECTOR_H
#define COMPONENT_DOCUMENTSELECTOR_H

#include <QWidget>

namespace Ui {
class componentDocumentSelector;
}

class ComponentDocumentSelector : public QWidget
{
    Q_OBJECT

public:
    explicit ComponentDocumentSelector(QWidget *parent = nullptr);
    ~ComponentDocumentSelector();

private:
    Ui::componentDocumentSelector *ui;

    void dummyContent();
    void connectSlots();

public slots:
    void newDocument();
    void openDocument();
    void documentFromTemplate();
};

#endif // COMPONENT_DOCUMENTSELECTOR_H
