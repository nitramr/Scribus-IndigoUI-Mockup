#ifndef ADVANCEDSPINBOX
#define ADVANCEDSPINBOX

#include <QDoubleSpinBox>


class AdvancedSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
    public:
        AdvancedSpinBox(QWidget *parent);
        ~AdvancedSpinBox() override;


};
#endif // ADVANCEDSPINBOX
