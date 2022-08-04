/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QComboBox>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLabel>

#include "sectioncontainer.h"

SectionContainer::SectionContainer(QWidget *parent)
    : QWidget(parent)
    , stackWidget(new QStackedWidget)
{
   // buttonCollapse->setObjectName(QStringLiteral("__qt__passive_comboBox"));

//    connect(buttonCollapse, QOverload<int>::of(&QComboBox::activated),
//            this, &MultiPageWidget::setCurrentIndex);

    boolIsCollapsible = true;
    boolIsCollapsed = false;


    // Label
    QFont m_font(this->font());
    m_font.setBold( true );
    labelTitle  = new QLabel("Title");
    labelTitle->setFont(m_font);

    // Buttons
    buttonCollapse = new QToolButton();
    buttonCollapse->setAutoRaise(true);
    buttonCollapse->adjustSize(); // needed to calculate the header height later

//    // Addon Layout
    addonLayout= new QHBoxLayout;
    addonLayout->setContentsMargins( 0,0,0,0 );
    addonLayout->setSpacing(4);

//    // Header Layout
    QHBoxLayout * headerLayout = new QHBoxLayout(this);
    headerLayout->addWidget( buttonCollapse );
    headerLayout->addWidget( labelTitle );
    headerLayout->addStretch( 0 );
    headerLayout->addLayout( addonLayout );
    headerLayout->setContentsMargins( 4,2,4,2 );

    // Header Widget
    headerWidget = new QWidget();
    headerWidget->setLayout(headerLayout);
    headerWidget->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Maximum );
    headerWidget->setMinimumHeight(buttonCollapse->height() + 4);

    // Main Layout
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(headerWidget);
    mainLayout->addWidget(stackWidget);

    // Size Policy
    QSizePolicy sizePol = QSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::Maximum );
    setSizePolicy(sizePol);

    // initial Setup
//    setIsCollapsible(isCollapsible);
    connectSlots();

}

QSize SectionContainer::sizeHint() const
{
    return QSize(200, 150);
}

void SectionContainer::addPage(QWidget *page)
{
    insertPage(count(), page);
}

void SectionContainer::removePage(int index)
{
    QWidget *widget = stackWidget->widget(index);
    stackWidget->removeWidget(widget);
}

int SectionContainer::count() const
{
    return stackWidget->count();
}

int SectionContainer::currentIndex() const
{
    return stackWidget->currentIndex();
}

void SectionContainer::insertPage(int index, QWidget *page)
{
    page->setParent(stackWidget);

    stackWidget->insertWidget(index, page);

}

void SectionContainer::setCurrentIndex(int index)
{
    if (index != currentIndex()) {
        stackWidget->setCurrentIndex(index);
        emit currentIndexChanged(index);
    }
}

QWidget* SectionContainer::widget(int index)
{
    return stackWidget->widget(index);
}

// =====================================================================================


void SectionContainer::setText(QString text)
{
    labelTitle->setText(text);
}

QString SectionContainer::text() const
{
    return labelTitle->text();
}

void SectionContainer::setIsCollapsible(bool isCollapsible)
{
    boolIsCollapsible = isCollapsible;
    buttonCollapse->setVisible(isCollapsible);
}

bool SectionContainer::isCollapsible()
{
    return boolIsCollapsible;
}

bool SectionContainer::isCollapsed()
{
    return boolIsCollapsed;
}

void SectionContainer::connectSlots()
{
    connect( buttonCollapse, &QToolButton::clicked,this, &SectionContainer::toggleCollpasedState );
}

void SectionContainer::toggleCollpasedState()
{
    if(isCollapsible() == false) return;

    ( boolIsCollapsed ) ? boolIsCollapsed = false : boolIsCollapsed = true;

    setIsCollapsed(boolIsCollapsed);
}

void SectionContainer::setIsCollapsed(bool state)
{
    if(isCollapsible() == false) return;

    boolIsCollapsed = state;

    if( boolIsCollapsed ){
        stackWidget->hide();
    //    buttonCollapse->setIcon(iconCollapsed);
        //this->setMaximumHeight(m_header->height());
    } else {
        stackWidget->show();
    //    buttonCollapse->setIcon(iconExpanded);
        //this->setMaximumHeight(QWIDGETSIZE_MAX);
    }

    emit collapsedState(boolIsCollapsed);
}
