#ifndef STYLEMANAGER_PARAGRAPH_H
#define STYLEMANAGER_PARAGRAPH_H

#include <QWidget>

namespace Ui {
class StyleManagerParagraph;
}

class StyleManagerParagraph : public QWidget
{
    Q_OBJECT

public:
    explicit StyleManagerParagraph(QWidget *parent = nullptr);
    ~StyleManagerParagraph();

private:
    Ui::StyleManagerParagraph *ui;

    void setup();
};

#endif // STYLEMANAGER_PARAGRAPH_H
