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
    $$PWD/src/ui/imageeffects \
    $$PWD/src/ui/panels \
    $$PWD/src/ui/quicktools \
    $$PWD/src/ui/toolbars \
    $$PWD/src/ui/widgets \
    $$PWD/src/ui/widgets/_combobox \
    $$PWD/src/utils


SOURCES += \
    src/api/api_application.cpp \
    src/color/colorblind.cpp \
    src/color/colorcomparison.cpp \
    src/color/colorconverter.cpp \
    src/color/colorspace.cpp \
    src/document/scribusdoc.cpp \
    src/main.cpp \
    src/manager/configuration_manager.cpp \
    src/manager/dirpaths_manager.cpp \
    src/manager/dock_manager.cpp \
    src/manager/icon_manager.cpp \
    src/manager/locale_manager.cpp \
    src/manager/menu_manager.cpp \
    src/manager/theme_manager.cpp \
    src/manager/toolbar_manager.cpp \
    src/manager/widget_manager.cpp \
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
    src/ui/components/component_curvewidget.cpp \
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
    src/ui/imageeffects/imageeffect_blur.cpp \
    src/ui/imageeffects/imageeffect_brightness.cpp \
    src/ui/imageeffects/imageeffect_colorize.cpp \
    src/ui/imageeffects/imageeffect_contrast.cpp \
    src/ui/imageeffects/imageeffect_curves.cpp \
    src/ui/imageeffects/imageeffect_grayscale.cpp \
    src/ui/imageeffects/imageeffect_invert.cpp \
    src/ui/imageeffects/imageeffect_posterize.cpp \
    src/ui/imageeffects/imageeffect_sharpen.cpp \
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
    src/ui/panels/panel_toolproperties.cpp \
    src/ui/quicktools/quicktool_layer.cpp \
    src/ui/quicktools/quicktool_preview.cpp \
    src/ui/splashscreen.cpp \
    src/ui/toolbars/toolbar_quicktools.cpp \
    src/ui/toolbars/toolbarproperty.cpp \
    src/ui/toolbars/toolbarproperty_arc.cpp \
    src/ui/toolbars/toolbarproperty_bezier.cpp \
    src/ui/toolbars/toolbarproperty_calligraphy.cpp \
    src/ui/toolbars/toolbarproperty_empty.cpp \
    src/ui/toolbars/toolbarproperty_gradient.cpp \
    src/ui/toolbars/toolbarproperty_measurement.cpp \
    src/ui/toolbars/toolbarproperty_polygon.cpp \
    src/ui/toolbars/toolbarproperty_spiral.cpp \
    src/ui/toolbars/toolbarproperty_table.cpp \
    src/ui/widgets/_combobox/unit_combobox.cpp \
    src/ui/widgets/advanced_spinbox/advanced_spinbox.cpp \
    src/ui/widgets/anglepicker/anglepicker.cpp \
    src/ui/widgets/basepoint_widget/basepoint_widget.cpp \
    src/ui/widgets/autoforms_button/autoforms_button.cpp \
    src/ui/widgets/color_button/color_button.cpp \
    src/ui/widgets/_combobox/arrowchooser_combobox.cpp \
    src/ui/widgets/_combobox/blendmode_combobox.cpp \
    src/ui/widgets/_combobox/firstpage_combobox.cpp \
    src/ui/widgets/_combobox/linetype_combobox.cpp \
    src/ui/widgets/colorblindness_button/colorblindness_button.cpp \
    src/ui/widgets/curveedit_widget/curveedit_widget.cpp \
    src/ui/widgets/headline_widget/headline_widget.cpp \
    src/ui/widgets/imageeffect_list/imageeffect_list.cpp \
    src/ui/widgets/stickypopup_widget/stickypopup.cpp \
    src/ui/widgets/colorharmony_wheel/colorharmony_wheel.cpp \
    src/ui/widgets/eyedropperscreen_widget/eyedropperscreen_widget.cpp \
    src/ui/imageeffects/imageeffect_item.cpp \
    src/ui/widgets/autoforms_menu/autoforms_menu.cpp \
    src/ui/widgets/popup_menu/popup_menu.cpp \
    src/ui/widgets/trashbin_widget/trashbin_widget.cpp \
    src/ui/widgets/color_listview/color_listview.cpp \
    src/ui/widgets/color_map/color_map.cpp \
    src/ui/widgets/color_slider/color_slider.cpp \
    src/ui/widgets/color_wheel/color_wheel.cpp \
    src/ui/widgets/dummydocument.cpp \
    src/ui/widgets/flow_layout/flow_layout.cpp \
    src/ui/widgets/form_widget/form_widget.cpp \
    src/ui/widgets/gradient_edit/gradient_edit.cpp \
    src/ui/widgets/gradient_preview/gradient_preview.cpp \
    src/ui/widgets/outline_viewer/outline_viewer.cpp \
    src/ui/widgets/page_list/page_list.cpp \
    src/ui/widgets/page_viewer/page_viewer.cpp \
    src/ui/widgets/section_container/section_container.cpp \
    src/utils/color_utils.cpp \
    src/utils/commonstrings.cpp \
    src/utils/file_utils.cpp \
    src/utils/math_utils.cpp \
    src/utils/render_utils.cpp \
    src/utils/spline_utils.cpp \
    src/utils/utils.cpp

HEADERS += \
    src/api/api_application.h \
    src/api/scribusapi.h \
    src/color/colorblind.h \
    src/color/colorcomparison.h \
    src/color/colorconverter.h \
    src/color/colorspace.h \
    src/document/scribusdoc.h \
    src/manager/configuration_manager.h \
    src/manager/dirpaths_manager.h \
    src/manager/dock_manager.h \
    src/manager/icon_manager.h \
    src/manager/locale_manager.h \
    src/manager/menu_manager.h \
    src/manager/theme_manager.h \
    src/manager/toolbar_manager.h \
    src/manager/widget_manager.h \
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
    src/ui/components/component_curvewidget.h \
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
    src/ui/imageeffects/imageeffect_blur.h \
    src/ui/imageeffects/imageeffect_brightness.h \
    src/ui/imageeffects/imageeffect_colorize.h \
    src/ui/imageeffects/imageeffect_contrast.h \
    src/ui/imageeffects/imageeffect_curves.h \
    src/ui/imageeffects/imageeffect_grayscale.h \
    src/ui/imageeffects/imageeffect_invert.h \
    src/ui/imageeffects/imageeffect_posterize.h \
    src/ui/imageeffects/imageeffect_sharpen.h \
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
    src/ui/panels/panel_toolproperties.h \
    src/ui/quicktools/quicktool_layer.h \
    src/ui/quicktools/quicktool_preview.h \
    src/ui/splashscreen.h \
    src/ui/toolbars/toolbar_quicktools.h \
    src/ui/toolbars/toolbarproperty.h \
    src/ui/toolbars/toolbarproperty_arc.h \
    src/ui/toolbars/toolbarproperty_bezier.h \
    src/ui/toolbars/toolbarproperty_calligraphy.h \
    src/ui/toolbars/toolbarproperty_empty.h \
    src/ui/toolbars/toolbarproperty_gradient.h \
    src/ui/toolbars/toolbarproperty_measurement.h \
    src/ui/toolbars/toolbarproperty_polygon.h \
    src/ui/toolbars/toolbarproperty_spiral.h \
    src/ui/toolbars/toolbarproperty_table.h \
    src/ui/widgets/_combobox/unit_combobox.h \
    src/ui/widgets/advanced_spinbox/advanced_spinbox.h \
    src/ui/widgets/anglepicker/anglepicker.h \
    src/ui/widgets/basepoint_widget/basepoint_widget.h \
    src/ui/widgets/autoforms_button/autoforms_button.h \
    src/ui/widgets/color_button/color_button.h \
    src/ui/widgets/_combobox/arrowchooser_combobox.h \
    src/ui/widgets/_combobox/blendmode_combobox.h \
    src/ui/widgets/_combobox/firstpage_combobox.h \
    src/ui/widgets/_combobox/linetype_combobox.h \
    src/ui/widgets/colorblindness_button/colorblindness_button.h \
    src/ui/widgets/curveedit_widget/curveedit_widget.h \
    src/ui/widgets/headline_widget/headline_widget.h \
    src/ui/widgets/imageeffect_list/imageeffect_list.h \
    src/ui/widgets/stickypopup_widget/stickypopup.h \
    src/ui/widgets/colorharmony_wheel/colorharmony_wheel.h \
    src/ui/widgets/eyedropperscreen_widget/eyedropperscreen_widget.h \
    src/ui/imageeffects/imageeffect_item.h \
    src/ui/widgets/autoforms_menu/autoforms_menu.h \
    src/ui/widgets/popup_menu/popup_menu.h \
    src/ui/widgets/trashbin_widget/trashbin_widget.h \
    src/ui/widgets/color_listview/color_listview.h \
    src/ui/widgets/color_map/color_map.h \
    src/ui/widgets/color_slider/color_slider.h \
    src/ui/widgets/color_wheel/color_wheel.h \
    src/ui/widgets/dummydocument.h \
    src/ui/widgets/flow_layout/flow_layout.h \
    src/ui/widgets/form_widget/form_widget.h \
    src/ui/widgets/gradient_edit/gradient_edit.h \
    src/ui/widgets/gradient_preview/gradient_preview.h \
    src/ui/widgets/outline_viewer/outline_viewer.h \
    src/ui/widgets/page_list/page_list.h \
    src/ui/widgets/page_viewer/page_viewer.h \
    src/ui/widgets/section_container/section_container.h \
    src/utils/color_utils.h \
    src/utils/commonstrings.h \
    src/utils/file_utils.h \
    src/utils/math_utils.h \
    src/utils/render_utils.h \
    src/utils/spline_utils.h \
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
    src/ui/components/component_curvewidget.ui \
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
    src/ui/imageeffects/imageeffect_blur.ui \
    src/ui/imageeffects/imageeffect_brightness.ui \
    src/ui/imageeffects/imageeffect_colorize.ui \
    src/ui/imageeffects/imageeffect_contrast.ui \
    src/ui/imageeffects/imageeffect_curves.ui \
    src/ui/imageeffects/imageeffect_grayscale.ui \
    src/ui/imageeffects/imageeffect_invert.ui \
    src/ui/imageeffects/imageeffect_posterize.ui \
    src/ui/imageeffects/imageeffect_sharpen.ui \
    src/ui/mainwindow.ui \
    src/ui/panels/panel_aligndistribute.ui \
    src/ui/panels/panel_content.ui \
    src/ui/panels/panel_content_image.ui \
    src/ui/panels/panel_content_text.ui \
    src/ui/panels/panel_frame.ui \
    src/ui/panels/panel_layers.ui \
    src/ui/panels/panel_outliner.ui \
    src/ui/panels/panel_pages.ui \
    src/ui/panels/panel_toolproperties.ui \
    src/ui/quicktools/quicktool_layer.ui \
    src/ui/quicktools/quicktool_preview.ui

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

