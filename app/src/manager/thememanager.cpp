/*
     This file base on code of:
     https://github.com/quassel/quassel/blob/master/src/uisupport/qssparser.h
 */


#include "thememanager.h"
#include <QDebug>
#include <QMetaEnum>
#include <QtMath>
#include <QRegularExpression>
#include <helper.h>
#include <QApplication>
#include <QPalette>
#include "configurationmanager.h"


ThemeManager* ThemeManager::m_instance = nullptr;

ThemeManager::ThemeManager(QObject *parent): QObject(parent)
{
    m_theme = "";
    m_styleSheet = "";


    // Init palette color groups

    _paletteColorGroups["active"]   = QPalette::Active;
    _paletteColorGroups["inactive"] = QPalette::Inactive;
    _paletteColorGroups["disabled"] = QPalette::Disabled;
    _paletteColorGroups["normal"]   = QPalette::Normal;


    // Init palette color roles

    _paletteColorRoles["alternate-base"]   = QPalette::AlternateBase;
    _paletteColorRoles["background"]       = QPalette::Window;  // background is depricated
    _paletteColorRoles["base"]             = QPalette::Base;
    _paletteColorRoles["bright-text"]      = QPalette::BrightText;
    _paletteColorRoles["button"]           = QPalette::Button;
    _paletteColorRoles["button-text"]      = QPalette::ButtonText;
    _paletteColorRoles["dark"]             = QPalette::Dark;
    _paletteColorRoles["foreground"]       = QPalette::WindowText; // foreground is depricated
    _paletteColorRoles["highlight"]        = QPalette::Highlight;
    _paletteColorRoles["highlighted-text"] = QPalette::HighlightedText;
    _paletteColorRoles["light"]            = QPalette::Light;
    _paletteColorRoles["link"]             = QPalette::Link;
    _paletteColorRoles["link-visited"]     = QPalette::LinkVisited;
    _paletteColorRoles["mid"]              = QPalette::Mid;
    _paletteColorRoles["midlight"]         = QPalette::Midlight;
    _paletteColorRoles["shadow"]           = QPalette::Shadow;
    _paletteColorRoles["text"]             = QPalette::Text;
    _paletteColorRoles["tooltip-base"]     = QPalette::ToolTipBase;
    _paletteColorRoles["tooltip-text"]     = QPalette::ToolTipText;
    _paletteColorRoles["window"]           = QPalette::Window;
    _paletteColorRoles["window-text"]      = QPalette::WindowText;


}

ThemeManager& ThemeManager::instance()
{
    static ThemeManager m_instance;
    return m_instance;
}

void ThemeManager::setup()
{
    QString theme = Helper::readFile(ConfigurationManager::files("app_default_theme"));
    parseTheme(theme);

    debugColorPalette("alternate-base", QPalette::AlternateBase);
    debugColorPalette("base", QPalette::Base);
    debugColorPalette("bright-text", QPalette::BrightText);
    debugColorPalette("button-text", QPalette::ButtonText);
    debugColorPalette("highlight", QPalette::Highlight);
    debugColorPalette("highlighted-text", QPalette::HighlightedText);
    debugColorPalette("link", QPalette::Link);
    debugColorPalette("link-visited", QPalette::LinkVisited);
    debugColorPalette("text", QPalette::Text);
    debugColorPalette("tooltip-base", QPalette::ToolTipBase);
    debugColorPalette("tooltip-text", QPalette::ToolTipText);
    debugColorPalette("window", QPalette::Window);
    debugColorPalette("window-text", QPalette::WindowText);
    debugColorPalette("light", QPalette::Light);
    debugColorPalette("midlight", QPalette::Midlight);
    debugColorPalette("button", QPalette::Button);
    debugColorPalette("mid", QPalette::Mid);
    debugColorPalette("dark", QPalette::Dark);
    debugColorPalette("shadow", QPalette::Shadow);


    qApp->setPalette(ThemeManager::instance().palette());
    qApp->setStyleSheet(ThemeManager::instance().styleSheet());
}


QString ThemeManager::themeName(){
    return m_theme;
}

QString ThemeManager::styleSheet()
{
    return m_styleSheet;
}



void ThemeManager::parseTheme(QString &styleString){


    if (styleString.isEmpty()) {
        qDebug("ThemeManager: Style string is empty!");
        return;
    }

    // Remove C-style comments /* */ or // from stylesheet
    QRegularExpression rx_comments("(\\/\\*[\\s\\S]*?(.*?)\\*\\/)|(\\/\\/.*)");
    styleString.remove(rx_comments);


    // Group 1: Palette tag
    // Group 2: theme (light or dark)
    // Group 3: {
    // Group 4: Styles
    // Group 5: }
    QRegularExpression rx_Palette("(Palette\\s*::)\\s*(light|dark)([^{]*\\{)([^\\}]+)(\\})");
    QRegularExpressionMatch mPalette = rx_Palette.match(styleString);

    if (!mPalette.hasMatch()) {
        qDebug("ThemeManager: Theme has no palette!");
        return;
    }

    m_theme            = mPalette.captured(2).trimmed();
    QString str_Styles   = mPalette.captured(4).trimmed();


    // Group 1: Group e.g. [all]
    // Group 2: Role e.g. button
    // Group 3: Color e.g. rgb(100,100,100)
    QRegularExpression rx_Settings("\\[(\\w+)\\]\\s*([a-zA-Z-]+)\\s*:\\s*([a-zA-Z#0-9-(),. ]*);\\s*");
    QRegularExpressionMatchIterator i = rx_Settings.globalMatch(str_Styles);

    while (i.hasNext()) {
        QRegularExpressionMatch mStyle = i.next();
        builtPalette(mStyle.captured(1).trimmed(), mStyle.captured(2).trimmed(), mStyle.captured(3).trimmed() );
        //str_Styles.remove(mStyle.capturedStart(), mStyle.capturedLength());

    }

    // Remove palette from stylesheet
    styleString.remove(rx_Palette);

    m_styleSheet = styleString;

    qDebug() << "ThemeManager: Theme name is" << m_theme;
}



void ThemeManager::builtPalette(QString group, QString role, QString color){

    QPalette::ColorGroup cg;
    QPalette::ColorRole cr;
    QColor c;

    // set Color Group
    if(!_paletteColorGroups.contains(group)){
        cg = QPalette::Normal;
    }else cg = _paletteColorGroups.value(group);


    // set Color Role
    if(!_paletteColorRoles.contains(role)) return;
    cr = _paletteColorRoles.value(role);


    // set Color
    c = parseColor(color);

    if(group == "all"){
        m_palette.setColor(cr, c);
    }else{
        m_palette.setColor(cg, cr, c);
    }



}



QColor ThemeManager::parseColor(const QString str)
{
    if (str.startsWith("rgba")) {
        QRegularExpression rx_rgba("\\(\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*\\)");
        QRegularExpressionMatch mRGBA = rx_rgba.match(str);

        if (mRGBA.hasMatch()) {
            qreal r = qBound(mRGBA.captured(1).toInt(),0,255);
            qreal g = qBound(mRGBA.captured(2).toInt(),0,255);
            qreal b = qBound(mRGBA.captured(3).toInt(),0,255);
            qreal a = qBound(mRGBA.captured(4).toDouble() / 100 *255,0.,255.);

            return QColor(r, g, b, a);
        }

    }
    else if (str.startsWith("rgb")) {
        QRegularExpression rx_rgb("\\(\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*\\)");
        QRegularExpressionMatch mRGB = rx_rgb.match(str);

        if (mRGB.hasMatch()) {
            qreal r = qBound(mRGB.captured(1).toInt(),0,255);
            qreal g = qBound(mRGB.captured(2).toInt(),0,255);
            qreal b = qBound(mRGB.captured(3).toInt(),0,255);

            return QColor(r, g, b);
        }

    }
    else if (str.startsWith("hsva")) {


        QRegularExpression rx_hsva("\\(\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*\\)");
        QRegularExpressionMatch mHSVA = rx_hsva.match(str);

        if (mHSVA.hasMatch()) {
            qreal h = qBound(mHSVA.captured(1).toDouble() / 360,0.,1.);
            qreal s = qBound(mHSVA.captured(2).toDouble() / 100,0.,1.);
            qreal v = qBound(mHSVA.captured(3).toDouble() / 100,0.,1.);
            qreal a = qBound(mHSVA.captured(4).toDouble() / 100,0.,1.);

            return QColor::fromHsvF(h, s, v, a);
        }

    }
    else if (str.startsWith("hsv")) {

        QRegularExpression rx_hsv("\\(\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*\\)");
        QRegularExpressionMatch mHSV = rx_hsv.match(str);

        if (mHSV.hasMatch()) {
            qreal h = qBound(mHSV.captured(1).toDouble() / 360,0.,1.);
            qreal s = qBound(mHSV.captured(2).toDouble() / 100,0.,1.);
            qreal v = qBound(mHSV.captured(3).toDouble() / 100,0.,1.);

            return QColor::fromHsvF(h, s, v);
        }

    }
    else if (str.startsWith("hsla")) {

        QRegularExpression rx_hsla("\\(\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*\\)");
        QRegularExpressionMatch mHSLA = rx_hsla.match(str);

        if (mHSLA.hasMatch()) {
            qreal h = qBound(mHSLA.captured(1).toDouble() / 360,0.,1.);
            qreal s = qBound(mHSLA.captured(2).toDouble() / 100,0.,1.);
            qreal l = qBound(mHSLA.captured(3).toDouble() / 100,0.,1.);
            qreal a = qBound(mHSLA.captured(4).toDouble() / 100,0.,1.);

            return QColor::fromHslF(h, s, l, a);
        }

    }
    else if (str.startsWith("hsl")) {

        QRegularExpression rx_hsl("\\(\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*,\\s*(\\d{1,3})\\s*\\)");
        QRegularExpressionMatch mHSL = rx_hsl.match(str);

        if (mHSL.hasMatch()) {
            qreal h = qBound(mHSL.captured(1).toDouble() / 360,0.,1.);
            qreal s = qBound(mHSL.captured(2).toDouble() / 100,0.,1.);
            qreal l = qBound(mHSL.captured(3).toDouble() / 100,0.,1.);

            return QColor::fromHslF(h, s, l);
        }

    }
    else {
        QRegularExpression rx("#?[0-9A-Fa-f]+");
        QRegularExpressionMatch mHex = rx.match(str);

        if (mHex.hasMatch()) {

            return QColor(mHex.captured(0));
        }
    }
    return QColor();
}

bool ThemeManager::isDark()
{
    return (m_theme == "dark") ? true : false;
}



void ThemeManager::debugColorPalette(QString key, QPalette::ColorRole role)
{

    QColor normal = qApp->palette().color(QPalette::Normal, role).toHsv();
    QColor disabled = qApp->palette().color(QPalette::Disabled, role).toHsv();
    QColor active = qApp->palette().color(QPalette::Active, role).toHsv();
    QColor inactive = qApp->palette().color(QPalette::Inactive, role).toHsv();


    qDebug().noquote() << QString("[normal]     %1:    hsl(%2,%3,%4);").arg(key).arg(qBound(0,normal.hue(), 359)).arg(normal.hslSaturationF()*100).arg(normal.lightnessF()*100);
    qDebug().noquote() << QString("[disabled]   %1:    hsl(%2,%3,%4);").arg(key).arg(qBound(0,disabled.hue(), 359)).arg(disabled.hslSaturationF()*100).arg(disabled.lightnessF()*100);
    qDebug().noquote() << QString("[active]     %1:    hsl(%2,%3,%4);").arg(key).arg(qBound(0,active.hue(), 359)).arg(active.hslSaturationF()*100).arg(active.lightnessF()*100);
    qDebug().noquote() << QString("[inactive]   %1:    hsl(%2,%3,%4);").arg(key).arg(qBound(0,inactive.hue(), 359)).arg(inactive.hslSaturationF()*100).arg(inactive.lightnessF()*100);


}
