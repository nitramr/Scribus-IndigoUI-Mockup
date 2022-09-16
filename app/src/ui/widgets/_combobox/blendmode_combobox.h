#ifndef BLENDMODE_COMBOBOX_H
#define BLENDMODE_COMBOBOX_H

#include <QComboBox>
#include <QWidget>

class BlendModeComboBox : public QComboBox
{
    Q_OBJECT
public:
    BlendModeComboBox(QWidget *parent = nullptr);
};

#endif // BLENDMODE_COMBOBOX_H
