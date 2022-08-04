#ifndef ACTION_H
#define ACTION_H

#include <QAction>



class Action : public QAction
{
public:
    Action(const QString &name, const QString &label, const QString &icon , QKeySequence keySequence = 0, QObject * parent = nullptr);

private:
    QString mName;
    QString mLabel;
    QString mIcon;
    QKeySequence m_KeySequence;


};

#endif // ACTION_H
