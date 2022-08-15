QT       += core gui xml svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

BIN_OUT = $${OUT_PWD}


# Advanced Dock
adsBuildStatic {
    DEFINES += ADS_STATIC
}

INCLUDEPATH += $$PWD/thirdparty/Qt-Advanced-Docking-System/src
DEPENDPATH += $$PWD/thirdparty/Qt-Advanced-Docking-System/src


# Third party  plugins
include ($$PWD/thirdparty/Qt-Advanced-Docking-System/ads.pri)

DESTDIR = $${BIN_OUT}/../bin

LIBS += -L$${BIN_OUT}/../bin

INCLUDEPATH += \
    $$PWD/src/api \
    $$PWD/src/color \
    $$PWD/src/document \
    $$PWD/src/manager \
    $$PWD/src/models \
    $$PWD/src/structs \
    $$PWD/src/templates \
    $$PWD/src/ui \
    $$PWD/src/ui/blocks \
    $$PWD/src/ui/colorpicker \
    $$PWD/src/ui/components \
    $$PWD/src/ui/delegate \
    $$PWD/src/ui/dialogs \
    $$PWD/src/ui/docks \
    $$PWD/src/ui/panels \    
    $$PWD/src/ui/widgets \
    $$PWD/src/ui/widgets/button \
    $$PWD/src/ui/widgets/color \
    $$PWD/src/ui/widgets/combobox \
    $$PWD/src/ui/widgets/container \
    $$PWD/src/ui/widgets/menu \
     $$PWD/src/ui/widgets/views \
    $$PWD/src/utils


SOURCES += \
    src/api/api_application.cpp \
    src/color/colorblind.cpp \
    src/color/colorcomparison.cpp \
    src/color/colorconverter.cpp \
    src/color/colorspace.cpp \
    src/document/scribusdoc.cpp \
    src/main.cpp \
    src/manager/actionmanager.cpp \
    src/manager/configurationmanager.cpp \
    src/manager/dirpathsmanager.cpp \
    src/manager/dockmanager.cpp \
    src/manager/iconmanager.cpp \
    src/manager/localemanager.cpp \
    src/manager/thememanager.cpp \
    src/models/action.cpp \
    src/models/colorlist.cpp \
    src/models/colorlistmodel.cpp \
    src/models/fpoint.cpp \
    src/models/fpointarray.cpp \
    src/models/sccolor.cpp \
    src/models/sclayers.cpp \
    src/models/vgradient.cpp \
    src/ui/blocks/block_alignment.cpp \
    src/ui/blocks/block_character.cpp \
    src/ui/blocks/block_character_advanced.cpp \
    src/ui/blocks/block_distribution.cpp \
    src/ui/blocks/block_dropshadow.cpp \
    src/ui/blocks/block_dropshadow_advanced.cpp \
    src/ui/blocks/block_fill.cpp \
    src/ui/blocks/block_fill_advanced.cpp \
    src/ui/blocks/block_image.cpp \
    src/ui/blocks/block_lists.cpp \
    src/ui/blocks/block_paragraph.cpp \
    src/ui/blocks/block_paragraph_advanced.cpp \
    src/ui/blocks/block_shape.cpp \
    src/ui/blocks/block_stroke.cpp \
    src/ui/blocks/block_stroke_advanced.cpp \
    src/ui/blocks/block_text_advanced.cpp \
    src/ui/blocks/block_text_alignment.cpp \
    src/ui/blocks/block_text_font.cpp \
    src/ui/blocks/block_text_outline.cpp \
    src/ui/blocks/block_textonpath.cpp \
    src/ui/blocks/block_xyz_advanced.cpp \
    src/ui/blocks/block_xyz_location.cpp \
    src/ui/blocks/block_xyz_transformation.cpp \
    src/ui/colorpicker/colorpicker.cpp \
    src/ui/colorpicker/colorpicker_color.cpp \
    src/ui/colorpicker/colorpicker_gradient.cpp \
    src/ui/colorpicker/colorswatches.cpp \
    src/ui/components/component_insertpage.cpp \
    src/ui/components/component_margins.cpp \
    src/ui/components/component_pagelayout.cpp \
    src/ui/components/component_parentpageselector.cpp \
    src/ui/components/component_spaceinput.cpp \
    src/ui/delegate/colorlistitemdelegate.cpp \
    src/ui/components/component_documentselector.cpp \
    src/ui/dialogs/dialog_colorswatchimport.cpp \
    src/ui/dialogs/dialog_duplicatepage.cpp \
    src/ui/dialogs/dialog_importpage.cpp \
    src/ui/dialogs/dialog_importparentpage.cpp \
    src/ui/dialogs/dialog_managepageproperties.cpp \
    src/ui/dialogs/dialog_movepage.cpp \
    src/ui/dialogs/dialog_newdocument.cpp \
    src/ui/dialogs/dialog_newpage.cpp \
    src/ui/dialogs/dialog_newparentpage.cpp \
    src/ui/docks/dock_centralwidget.cpp \
    src/ui/docks/dock_documentbase.cpp \
    src/ui/docks/dock_panelbase.cpp \
    src/ui/mainwindow.cpp \
    src/ui/panels/panel_aligndistribute.cpp \
    src/ui/panels/panel_content.cpp \
    src/ui/panels/panel_content_image.cpp \
    src/ui/panels/panel_content_text.cpp \
    src/ui/panels/panel_frame.cpp \
    src/ui/panels/panel_layers.cpp \
    src/ui/panels/panel_outliner.cpp \
    src/ui/panels/panel_pages.cpp \
    src/ui/panels/panel_test.cpp \
    src/ui/splashscreen.cpp \
    src/ui/widgets/advancedspinbox.cpp \
    src/ui/widgets/anglepicker.cpp \
    src/ui/widgets/basepointwidget.cpp \
    src/ui/widgets/menu/menu_autoforms.cpp \
    src/ui/widgets/button/button_autoforms.cpp \
    src/ui/widgets/button/colorbutton.cpp \
    src/ui/widgets/color/colorharmonywheel.cpp \
    src/ui/widgets/views/colorlistview.cpp \
    src/ui/widgets/color/colormap.cpp \
    src/ui/widgets/color/colorslider.cpp \
    src/ui/widgets/color/colorwheel.cpp \
    src/ui/widgets/combobox/combobox_arrowchooser.cpp \
    src/ui/widgets/combobox/combobox_firstpage.cpp \
    src/ui/widgets/combobox/combobox_blendmode.cpp \
    src/ui/widgets/combobox/combobox_linetype.cpp \
    src/ui/widgets/dummydocument.cpp \
    src/ui/widgets/container/flowlayout.cpp \
    src/ui/widgets/container/formwidget.cpp \
    src/ui/delegate/listwidgetitemdelegate.cpp \
    src/ui/widgets/color/gradientedit.cpp \
    src/ui/widgets/color/gradientpreview.cpp \
    src/ui/widgets/menu/menu_popup.cpp \
    src/ui/widgets/views/outlineviewer.cpp \
    src/ui/widgets/views/pagelist.cpp \
    src/ui/widgets/views/pageviewer.cpp \
    src/ui/widgets/container/sectioncontainer.cpp \
    src/ui/widgets/trashbin.cpp \
    src/utils/commonstrings.cpp \
    src/utils/helper.cpp \
    src/utils/util.cpp \
    src/utils/util_color.cpp \
    src/utils/util_math.cpp

HEADERS += \
    src/api/api_application.h \
    src/api/scribusapi.h \
    src/color/colorblind.h \
    src/color/colorcomparison.h \
    src/color/colorconverter.h \
    src/color/colorspace.h \
    src/document/scribusdoc.h \
    src/manager/actionmanager.h \
    src/manager/configurationmanager.h \
    src/manager/dirpathsmanager.h \
    src/manager/dockmanager.h \
    src/manager/iconmanager.h \
    src/manager/localemanager.h \
    src/manager/thememanager.h \
    src/models/action.h \
    src/models/colorlist.h \
    src/models/colorlistmodel.h \
    src/models/fpoint.h \
    src/models/fpointarray.h \
    src/models/sclayers.h \
    src/models/vgradient.h \
    src/structs/colorpixmapvalue.h \
    src/structs/prefsstructs.h \
    src/structs/structs.h \
    src/ui/blocks/block_alignment.h \
    src/ui/blocks/block_character.h \
    src/ui/blocks/block_character_advanced.h \
    src/ui/blocks/block_distribution.h \
    src/ui/blocks/block_dropshadow.h \
    src/ui/blocks/block_dropshadow_advanced.h \
    src/ui/blocks/block_fill_advanced.h \
    src/ui/blocks/block_image.h \
    src/ui/blocks/block_lists.h \
    src/ui/blocks/block_paragraph.h \
    src/ui/blocks/block_paragraph_advanced.h \
    src/ui/blocks/block_stroke.h \
    src/ui/blocks/block_stroke_advanced.h \
    src/ui/blocks/block_text_advanced.h \
    src/ui/blocks/block_text_alignment.h \
    src/ui/blocks/block_text_font.h \
    src/ui/blocks/block_text_outline.h \
    src/ui/blocks/block_textonpath.h \
    src/ui/colorpicker/colorpicker_color.h \
    src/ui/colorpicker/colorpicker_gradient.h \
    src/ui/colorpicker/colorswatches.h \
    src/ui/components/component_insertpage.h \
    src/ui/components/component_margins.h \
    src/ui/components/component_pagelayout.h \
    src/ui/components/component_parentpageselector.h \
    src/ui/components/component_spaceinput.h \
    src/ui/delegate/colorlistitemdelegate.h \
    src/models/sccolor.h \
    src/structs/enums.h \
    src/templates/pixmapcache.h \
    src/templates/scguardedptr.h \
    src/ui/blocks/block_fill.h \
    src/ui/blocks/block_shape.h \
    src/ui/blocks/block_xyz_advanced.h \
    src/ui/blocks/block_xyz_location.h \
    src/ui/blocks/block_xyz_transformation.h \
    src/ui/colorpicker/colorpicker.h \
    src/ui/components/component_documentselector.h \
    src/ui/delegate/sclistboxpixmap.h \
    src/ui/dialogs/dialog_colorswatchimport.h \
    src/ui/dialogs/dialog_duplicatepage.h \
    src/ui/dialogs/dialog_importpage.h \
    src/ui/dialogs/dialog_importparentpage.h \
    src/ui/dialogs/dialog_managepageproperties.h \
    src/ui/dialogs/dialog_movepage.h \
    src/ui/dialogs/dialog_newdocument.h \
    src/ui/dialogs/dialog_newpage.h \
    src/ui/dialogs/dialog_newparentpage.h \
    src/ui/docks/dock_centralwidget.h \
    src/ui/docks/dock_documentbase.h \
    src/ui/docks/dock_panelbase.h \
    src/ui/mainwindow.h \
    src/ui/panels/panel_aligndistribute.h \
    src/ui/panels/panel_content.h \
    src/ui/panels/panel_content_image.h \
    src/ui/panels/panel_content_text.h \
    src/ui/panels/panel_frame.h \
    src/ui/panels/panel_layers.h \
    src/ui/panels/panel_outliner.h \
    src/ui/panels/panel_pages.h \
    src/ui/panels/panel_test.h \
    src/ui/splashscreen.h \
    src/ui/widgets/advancedspinbox.h \
    src/ui/widgets/anglepicker.h \
    src/ui/widgets/basepointwidget.h \
    src/ui/widgets/menu/menu_autoforms.h \
    src/ui/widgets/button/button_autoforms.h \
    src/ui/widgets/button/colorbutton.h \
    src/ui/widgets/color/colorharmonywheel.h \
    src/ui/widgets/views/colorlistview.h \
    src/ui/widgets/color/colormap.h \
    src/ui/widgets/color/colorslider.h \
    src/ui/widgets/color/colorwheel.h \
    src/ui/widgets/combobox/combobox_arrowchooser.h \
    src/ui/widgets/combobox/combobox_firstpage.h \
    src/ui/widgets/combobox/combobox_blendmode.h \
    src/ui/widgets/combobox/combobox_linetype.h \
    src/ui/widgets/dummydocument.h \
    src/ui/widgets/container/flowlayout.h \
    src/ui/widgets/container/formwidget.h \
    src/ui/delegate/listwidgetitemdelegate.h \
    src/ui/widgets/color/gradientedit.h \
    src/ui/widgets/color/gradientpreview.h \
    src/ui/widgets/menu/menu_popup.h \
    src/ui/widgets/views/outlineviewer.h \
    src/ui/widgets/views/pagelist.h \
    src/ui/widgets/views/pageviewer.h \
    src/ui/widgets/container/sectioncontainer.h \
    src/ui/widgets/trashbin.h \
    src/utils/commonstrings.h \
    src/utils/helper.h \
    src/utils/util.h \
    src/utils/util_color.h \
    src/utils/util_math.h


FORMS += \
    src/ui/blocks/block_alignment.ui \
    src/ui/blocks/block_character.ui \
    src/ui/blocks/block_character_advanced.ui \
    src/ui/blocks/block_distribution.ui \
    src/ui/blocks/block_dropshadow.ui \
    src/ui/blocks/block_dropshadow_advanced.ui \
    src/ui/blocks/block_fill.ui \
    src/ui/blocks/block_fill_advanced.ui \
    src/ui/blocks/block_image.ui \
    src/ui/blocks/block_lists.ui \
    src/ui/blocks/block_paragraph.ui \
    src/ui/blocks/block_paragraph_advanced.ui \
    src/ui/blocks/block_shape.ui \
    src/ui/blocks/block_stroke.ui \
    src/ui/blocks/block_stroke_advanced.ui \
    src/ui/blocks/block_text_advanced.ui \
    src/ui/blocks/block_text_alignment.ui \
    src/ui/blocks/block_text_font.ui \
    src/ui/blocks/block_text_outline.ui \
    src/ui/blocks/block_textonpath.ui \
    src/ui/blocks/block_xyz_advanced.ui \
    src/ui/blocks/block_xyz_location.ui \
    src/ui/blocks/block_xyz_transformation.ui \
    src/ui/colorpicker/colorpicker.ui \
    src/ui/colorpicker/colorpicker_color.ui \
    src/ui/colorpicker/colorpicker_gradient.ui \
    src/ui/colorpicker/colorswatches.ui \
    src/ui/components/component_insertpage.ui \
    src/ui/components/component_margins.ui \
    src/ui/components/component_pagelayout.ui \
    src/ui/components/component_parentpageselector.ui \
    src/ui/components/component_spaceinput.ui \
    src/ui/components/component_documentselector.ui \
    src/ui/dialogs/dialog_colorswatchimport.ui \
    src/ui/dialogs/dialog_duplicatepage.ui \
    src/ui/dialogs/dialog_importpage.ui \
    src/ui/dialogs/dialog_importparentpage.ui \
    src/ui/dialogs/dialog_managepageproperties.ui \
    src/ui/dialogs/dialog_movepage.ui \
    src/ui/dialogs/dialog_newdocument.ui \
    src/ui/dialogs/dialog_newpage.ui \
    src/ui/dialogs/dialog_newparentpage.ui \
    src/ui/mainwindow.ui \
    src/ui/panels/panel_aligndistribute.ui \
    src/ui/panels/panel_content.ui \
    src/ui/panels/panel_content_image.ui \
    src/ui/panels/panel_content_text.ui \
    src/ui/panels/panel_frame.ui \
    src/ui/panels/panel_layers.ui \
    src/ui/panels/panel_outliner.ui \
    src/ui/panels/panel_pages.ui \
    src/ui/panels/panel_test.ui

TRANSLATIONS += \
    Scribus-IndigoUI_en_US.ts


CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc

