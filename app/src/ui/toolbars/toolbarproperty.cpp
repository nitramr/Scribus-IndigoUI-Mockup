#include "toolbarproperty.h"
#include "form_widget/form_widget.h"

#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QToolButton>

ToolBarProperty::ToolBarProperty(QWidget * parent) : QToolBar(parent)
{

    m_icon = new QLabel();
    m_pixmap = QPixmap();
    m_formWidgets = new QMap<QString,QAction*>();

    this->setMovable(false);
    this->setFloatable(false);
    this->setOrientation(Qt::Horizontal);
    this->setAllowedAreas(Qt::TopToolBarArea);
    this->setMinimumHeight( minHeight() );

    this->addSpacing(8);
    this->addWidget(m_icon);
    this->addSpacing(8);


}

void ToolBarProperty::setIcon(QPixmap icon)
{
    m_pixmap = icon;

    if(!icon.isNull()){
        icon = icon.scaledToHeight( iconSize().height(), Qt::SmoothTransformation);
    }

    m_icon->setPixmap( icon );
}

void ToolBarProperty::addSpacing(int spacing)
{
    QLabel *label = new QLabel(this);
    addWidget(label);
    label->setFixedWidth(spacing);
}

FormWidget *ToolBarProperty::addFormWidget(QString key, QString label, QList<QWidget *> widgets)
{
    QHBoxLayout *m_layout = new QHBoxLayout();
    m_layout->setContentsMargins(0,0,8,0);
    m_layout->setSpacing(4);
    FormWidget *frm = nullptr;

    if(m_formWidgets->contains(key)){

        QAction *action = m_formWidgets->value(key);

        if(action){

            QWidget * widget = this->widgetForAction(action);
            frm = qobject_cast<FormWidget*>(widget);

            if(frm){

                frm->setDirection(FormWidget::Left);
                frm->setLayout(m_layout);
                frm->setLabel(label);

                foreach( QWidget* widget, widgets )
                {
                    m_layout->addWidget(widget);

                }
            }
        }

    }else{
        frm = new FormWidget();
        frm->setDirection(FormWidget::Left);
        frm->setLayout(m_layout);
        frm->setLabel(label);

        foreach( QWidget* widget, widgets )
        {
            m_layout->addWidget(widget);

        }

        QAction * action = addWidget(frm);
        m_formWidgets->insert(key, action);

    }

    return frm;
}

FormWidget *ToolBarProperty::formWidget(QString key)
{
    FormWidget *frm = nullptr;

    if(m_formWidgets->contains(key)){

        QAction * action = m_formWidgets->value(key);

        if(action){
            QWidget * widget = this->widgetForAction(action);
            frm = qobject_cast<FormWidget*>(widget);
            return frm;
        }
    }

    return frm;
}

void ToolBarProperty::setFormWidgetVisibility(QString key, bool visible)
{
    if(m_formWidgets->contains(key)){

        QAction * action = m_formWidgets->value(key);

        if(action){
            action->setVisible(visible);
        }

    }
}

void ToolBarProperty::setFormWidgetLabel(QString key, QString label)
{
    FormWidget * frm = formWidget(key);

    if(frm){
        frm->setLabel(label);
    }

}

void ToolBarProperty::setIconSize(const QSize &iconSize)
{
    QToolBar::setIconSize(iconSize);

    setIcon(m_pixmap);
    this->setMinimumHeight( minHeight() );
}

int ToolBarProperty::minHeight()
{
    //    QFont fontLabel = this->font();
    //    fontLabel.setPointSize(8);

    //    QDoubleSpinBox *spinBox = new QDoubleSpinBox();

    //    QHBoxLayout *layout = new QHBoxLayout;
    //    layout->addWidget(spinBox);
    //    layout->setContentsMargins(0,0,0,0);

    //    FormWidget * form = new FormWidget();
    //    form->setLabel(tr("Start Angle"));
    //    form->setLayout(layout);
    //    form->setFont(fontLabel);
    //    form->adjustSize();

    //    return form->height();

   // return 40;

    return iconSize().height() + 16;

}
