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

#include <QtDesigner/QExtensionFactory>
#include <QtDesigner/QExtensionManager>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QDesignerFormWindowInterface>
#include <QtDesigner/QDesignerContainerExtension>
#include <QtDesigner/QDesignerPropertySheetExtension>

#include <QIcon>
#include <QtPlugin>

#include "section_container/section_container.h"
#include "sectioncontainerplugin.h"
#include "sectioncontainerextensionfactory.h"

SectionContainerPlugin::SectionContainerPlugin(QObject *parent)
    : QObject(parent)
{
}

QString SectionContainerPlugin::name() const
{
    return QLatin1String("SectionContainer");
}

QString SectionContainerPlugin::group() const
{
    return QLatin1String("Indigo UI");
}

QString SectionContainerPlugin::toolTip() const
{
    return QString();
}

QString SectionContainerPlugin::whatsThis() const
{
    return QString();
}

QString SectionContainerPlugin::includeFile() const
{
    return QLatin1String("section_container/section_container.h");
}

QIcon SectionContainerPlugin::icon() const
{
    return QIcon();
}

bool SectionContainerPlugin::isContainer() const
{
    return true;
}

QWidget *SectionContainerPlugin::createWidget(QWidget *parent)
{
    SectionContainer *widget = new SectionContainer(parent);
    connect(widget, &SectionContainer::currentIndexChanged,
            this, &SectionContainerPlugin::currentIndexChanged);
    return widget;
}

bool SectionContainerPlugin::isInitialized() const
{
    return initialized;
}

void SectionContainerPlugin::initialize(QDesignerFormEditorInterface *formEditor)
{
    if (initialized)
        return;

    QExtensionManager *manager = formEditor->extensionManager();
    QExtensionFactory *factory = new SectionContainerExtensionFactory(manager);

    Q_ASSERT(manager != 0);
    manager->registerExtensions(factory, Q_TYPEID(QDesignerContainerExtension));

    initialized = true;
}

QString SectionContainerPlugin::domXml() const
{
    return QLatin1String(R"(
<ui language="c++"  displayname="Section Container">
    <widget class="SectionContainer" name="sectionContainer">
     <property name="font">
      <font>
       <bold>true</bold>
      </font>
     </property>
     <widget class="QWidget" name="page">
      <layout class="QVBoxLayout" name="verticalLayout"/>
     </widget>
    </widget>
    <customwidgets>
        <customwidget>
            <class>SectionContainer</class>
            <extends>QWidget</extends>
            <addpagemethod>addPage</addpagemethod>
        </customwidget>
    </customwidgets>
</ui>)");
}

void SectionContainerPlugin::currentIndexChanged(int index)
{
    Q_UNUSED(index);
    SectionContainer *widget = qobject_cast<SectionContainer*>(sender());

    if (widget) {
        QDesignerFormWindowInterface *form = QDesignerFormWindowInterface::findFormWindow(widget);
        if (form)
            form->emitSelectionChanged();
    }
}
