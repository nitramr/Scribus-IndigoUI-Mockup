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
    src/manager/action_manager.cpp \
    src/manager/configuration_manager.cpp \
    src/manager/dirpaths_manager.cpp \
    src/manager/dock_manager.cpp \
    src/manager/icon_manager.cpp \
    src/manager/locale_manager.cpp \
    src/manager/theme_manager.cpp \
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
    src/ui/blocks/block_imageeffects.cpp \
    src/ui/blocks/block_lists.cpp \
    src/ui/blocks/block_paragraph.cpp \
    src/ui/blocks/block_paragraph_advanced.cpp \
    src/ui/blocks/block_shape.cpp \
    src/ui/blocks/block_stroke.cpp \
    src/ui/blocks/block_stroke_advanced.cpp \
    src/ui/blocks/block_text_advanced.cpp \
    src/ui/blocks/block_text_font.cpp \
    src/ui/blocks/block_text_outline.cpp \
    src/ui/blocks/block_textonpath.cpp \
    src/ui/blocks/block_xyz_advanced.cpp \
    src/ui/blocks/block_xyz_location.cpp \
    src/ui/colorpicker/colorpicker.cpp \
    src/ui/colorpicker/colorpicker_color.cpp \
    src/ui/colorpicker/colorpicker_gradient.cpp \
    src/ui/colorpicker/colorswatches.cpp \
    src/ui/colorpicker/eyedropperscreen_widget.cpp \
    src/ui/components/component_insertpage.cpp \
    src/ui/components/component_margins.cpp \
    src/ui/components/component_pagelayout.cpp \
    src/ui/components/component_parentpageselector.cpp \
    src/ui/components/component_spaceinput.cpp \
    src/ui/components/component_documentselector.cpp \
    src/ui/delegate/colorlistitem_delegate.cpp \
    src/ui/delegate/documentlistitem_delegate.cpp \
    src/ui/dialogs/colorswatchimport_dialog.cpp \
    src/ui/dialogs/duplicatepage_dialog.cpp \
    src/ui/dialogs/importpage_dialog.cpp \
    src/ui/dialogs/importparentpage_dialog.cpp \
    src/ui/dialogs/managepageproperties_dialog.cpp \
    src/ui/dialogs/movepage_dialog.cpp \
    src/ui/dialogs/newdocument_dialog.cpp \
    src/ui/dialogs/newpage_dialog.cpp \
    src/ui/dialogs/newparentpage_dialog.cpp \
    src/ui/docks/dock_centralwidget.cpp \
    src/ui/docks/dock_documentbase.cpp \
    src/ui/docks/dock_panelbase.cpp \
    src/ui/mainwindow.cpp \
    src/ui/panels/panel.cpp \
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
    src/ui/widgets/basepoint_widget.cpp \
    src/ui/widgets/button/autoforms_button.cpp \
    src/ui/widgets/button/color_button.cpp \
    src/ui/widgets/combobox/arrowchooser_combobox.cpp \
    src/ui/widgets/combobox/blendmode_combobox.cpp \
    src/ui/widgets/combobox/firstpage_combobox.cpp \
    src/ui/widgets/combobox/linetype_combobox.cpp \
    src/ui/widgets/container/headline_widget.cpp \
    src/ui/widgets/container/stickypopup.cpp \
    src/ui/widgets/color/colorharmonywheel.cpp \
    src/ui/widgets/imageeffects/imageeffect_item.cpp \
    src/ui/widgets/menu/autoforms_menu.cpp \
    src/ui/widgets/menu/popup_menu.cpp \
    src/ui/widgets/trashbin_widget.cpp \
    src/ui/widgets/views/colorlistview.cpp \
    src/ui/widgets/color/colormap.cpp \
    src/ui/widgets/color/colorslider.cpp \
    src/ui/widgets/color/colorwheel.cpp \
    src/ui/widgets/dummydocument.cpp \
    src/ui/widgets/container/flowlayout.cpp \
    src/ui/widgets/container/formwidget.cpp \
    src/ui/widgets/color/gradientedit.cpp \
    src/ui/widgets/color/gradientpreview.cpp \
    src/ui/widgets/views/outlineviewer.cpp \
    src/ui/widgets/views/pagelist.cpp \
    src/ui/widgets/views/pageviewer.cpp \
    src/ui/widgets/container/sectioncontainer.cpp \
    src/utils/color_utils.cpp \
    src/utils/commonstrings.cpp \
    src/utils/file_utils.cpp \
    src/utils/math_utils.cpp \
    src/utils/render_utils.cpp \
    src/utils/utils.cpp

HEADERS += \
    src/api/api_application.h \
    src/api/scribusapi.h \
    src/color/colorblind.h \
    src/color/colorcomparison.h \
    src/color/colorconverter.h \
    src/color/colorspace.h \
    src/document/scribusdoc.h \
    src/manager/action_manager.h \
    src/manager/configuration_manager.h \
    src/manager/dirpaths_manager.h \
    src/manager/dock_manager.h \
    src/manager/icon_manager.h \
    src/manager/locale_manager.h \
    src/manager/theme_manager.h \
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
    src/ui/blocks/block_imageeffects.h \
    src/ui/blocks/block_lists.h \
    src/ui/blocks/block_paragraph.h \
    src/ui/blocks/block_paragraph_advanced.h \
    src/ui/blocks/block_stroke.h \
    src/ui/blocks/block_stroke_advanced.h \
    src/ui/blocks/block_text_advanced.h \
    src/ui/blocks/block_text_font.h \
    src/ui/blocks/block_text_outline.h \
    src/ui/blocks/block_textonpath.h \
    src/ui/colorpicker/colorpicker_color.h \
    src/ui/colorpicker/colorpicker_gradient.h \
    src/ui/colorpicker/colorswatches.h \
    src/ui/colorpicker/eyedropperscreen_widget.h \
    src/ui/components/component_insertpage.h \
    src/ui/components/component_margins.h \
    src/ui/components/component_pagelayout.h \
    src/ui/components/component_parentpageselector.h \
    src/ui/components/component_spaceinput.h \
    src/models/sccolor.h \
    src/structs/enums.h \
    src/templates/pixmapcache.h \
    src/templates/scguardedptr.h \
    src/ui/blocks/block_fill.h \
    src/ui/blocks/block_shape.h \
    src/ui/blocks/block_xyz_advanced.h \
    src/ui/blocks/block_xyz_location.h \
    src/ui/colorpicker/colorpicker.h \
    src/ui/components/component_documentselector.h \
    src/ui/delegate/colorlistitem_delegate.h \
    src/ui/delegate/documentlistitem_delegate.h \
    src/ui/delegate/sclistboxpixmap.h \
    src/ui/dialogs/colorswatchimport_dialog.h \
    src/ui/dialogs/duplicatepage_dialog.h \
    src/ui/dialogs/importpage_dialog.h \
    src/ui/dialogs/importparentpage_dialog.h \
    src/ui/dialogs/managepageproperties_dialog.h \
    src/ui/dialogs/movepage_dialog.h \
    src/ui/dialogs/newdocument_dialog.h \
    src/ui/dialogs/newpage_dialog.h \
    src/ui/dialogs/newparentpage_dialog.h \
    src/ui/docks/dock_centralwidget.h \
    src/ui/docks/dock_documentbase.h \
    src/ui/docks/dock_panelbase.h \
    src/ui/mainwindow.h \
    src/ui/panels/panel.h \
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
    src/ui/widgets/basepoint_widget.h \
    src/ui/widgets/button/autoforms_button.h \
    src/ui/widgets/button/color_button.h \
    src/ui/widgets/combobox/arrowchooser_combobox.h \
    src/ui/widgets/combobox/blendmode_combobox.h \
    src/ui/widgets/combobox/firstpage_combobox.h \
    src/ui/widgets/combobox/linetype_combobox.h \
    src/ui/widgets/container/headline_widget.h \
    src/ui/widgets/container/stickypopup.h \
    src/ui/widgets/color/colorharmonywheel.h \
    src/ui/widgets/imageeffects/imageeffect_item.h \
    src/ui/widgets/menu/autoforms_menu.h \
    src/ui/widgets/menu/popup_menu.h \
    src/ui/widgets/trashbin_widget.h \
    src/ui/widgets/views/colorlistview.h \
    src/ui/widgets/color/colormap.h \
    src/ui/widgets/color/colorslider.h \
    src/ui/widgets/color/colorwheel.h \
    src/ui/widgets/dummydocument.h \
    src/ui/widgets/container/flowlayout.h \
    src/ui/widgets/container/formwidget.h \
    src/ui/widgets/color/gradientedit.h \
    src/ui/widgets/color/gradientpreview.h \
    src/ui/widgets/views/outlineviewer.h \
    src/ui/widgets/views/pagelist.h \
    src/ui/widgets/views/pageviewer.h \
    src/ui/widgets/container/sectioncontainer.h \
    src/utils/color_utils.h \
    src/utils/commonstrings.h \
    src/utils/file_utils.h \
    src/utils/math_utils.h \
    src/utils/render_utils.h \
    src/utils/utils.h


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
    src/ui/blocks/block_imageeffects.ui \
    src/ui/blocks/block_lists.ui \
    src/ui/blocks/block_paragraph.ui \
    src/ui/blocks/block_paragraph_advanced.ui \
    src/ui/blocks/block_shape.ui \
    src/ui/blocks/block_stroke.ui \
    src/ui/blocks/block_stroke_advanced.ui \
    src/ui/blocks/block_text_advanced.ui \
    src/ui/blocks/block_text_font.ui \
    src/ui/blocks/block_text_outline.ui \
    src/ui/blocks/block_textonpath.ui \
    src/ui/blocks/block_xyz_advanced.ui \
    src/ui/blocks/block_xyz_location.ui \
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
    src/ui/dialogs/colorswatchimport_dialog.ui \
    src/ui/dialogs/duplicatepage_dialog.ui \
    src/ui/dialogs/importpage_dialog.ui \
    src/ui/dialogs/importparentpage_dialog.ui \
    src/ui/dialogs/managepageproperties_dialog.ui \
    src/ui/dialogs/movepage_dialog.ui \
    src/ui/dialogs/newdocument_dialog.ui \
    src/ui/dialogs/newpage_dialog.ui \
    src/ui/dialogs/newparentpage_dialog.ui \
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

