#ifndef ADVANCEDSPINBOX
#define ADVANCEDSPINBOX

#include <QDoubleSpinBox>


class AdvancedSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
    public:
        AdvancedSpinBox(QWidget *parent = nullptr);
        ~AdvancedSpinBox() override;


};
#endif // ADVANCEDSPINBOX
