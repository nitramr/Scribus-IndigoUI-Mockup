#ifndef IMAGEEFFECTITEM_H
#define IMAGEEFFECTITEM_H

#include "section_container/section_container.h"
#include <QCheckBox>

class ImageEffectItem : public SectionContainer
{
    Q_OBJECT
public:
    ImageEffectItem(QString title, bool isCollapsible = true, QWidget * parent = nullptr);

private:
    QCheckBox * checkBoxEffect;
    QToolButton * buttonDelete;

    void setup();
};

#endif // IMAGEEFFECTITEM_H
