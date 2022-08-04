#include "action.h"

#include <iconmanager.h>

Action::Action(const QString &name, const QString &label, const QString &icon, QKeySequence keySequence, QObject *parent) :
    QAction(label, parent),
    mName(name),
    mIcon(icon),
    m_KeySequence(keySequence)

{
    if(mIcon != ""){
        this->setIcon(IconManager::instance().icon(mIcon));
    }

}
