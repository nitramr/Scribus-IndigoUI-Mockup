#ifndef IMAGEEFFECTITEM_H
#define IMAGEEFFECTITEM_H

#include "sectioncontainer.h"
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
