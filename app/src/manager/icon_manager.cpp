#include "icon_manager.h"

#include <QCursor>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDomElement>
#include <QApplication>
#include <QPalette>
#include <QPainter>
#include <QSvgRenderer>
#include <QRegularExpression>
#include <QPainterPath>
#include <QMap>

#include "configuration_manager.h"
#include "theme_manager.h"
#include "dirpaths_manager.h"
#include "api_application.h"

IconManager* IconManager::m_instance = nullptr;

const QString classDark = "onDark";
const QString tagIcon = "icon";
const QString colorOnDark = "onDark";
const QString colorOnLight = "onLight";

IconManager::IconManager(QObject *parent)
    : QObject(parent)
{
    m_forDarkMode = false;

}


IconManager& IconManager::instance()
{
    static IconManager m_instance;
    return m_instance;
}


bool IconManager::setup()
{
    if (!initIconSets())
    {
        qWarning()<<"No icons found :(";
        return false;
    }

    if (!createCache())
    {
        qWarning()<<"Can't load icons from iconset.";
        return false;
    }

    return true;
}

QCursor IconManager::cursor(const QString &name, int hotX, int hotY)
{
    return QCursor(pixmap(name), hotX, hotY);
}

QIcon IconManager::icon(const QString& name)
{
    return QIcon(pixmap(name));
}

QPixmap IconManager::pixmap(const QString &name)
{
    if (m_pxCache.contains(name)){
        return *m_pxCache[name];
    }else{
        qWarning() << "IconManager: No icon with name '" + name + "' in icon cache.";
        return QPixmap();
    }

}

void IconManager::addIcon(const QString &name, QPainterPath path)
{
    if (!m_pxCache.contains(name)){
        m_iconPaths.insert(name, &path);
        m_pxCache.insert(name, renderPath(path));
    }else {
        qWarning() << "IconManager: Icon with name '" + name + "' already exists in cache.";
    }
}

void IconManager::setIconsForDarkMode(bool forDarkMode)
{
    m_forDarkMode = forDarkMode;

}

QColor IconManager::baseColor()
{
    return qApp->palette().windowText().color();
}

void IconManager::clearCache()
{
    m_pxCache.clear();
}

void IconManager::rebuildCache()
{
    clearCache();

    // add icons from icon set
    if (!createCache())
    {
        qWarning()<<"IconManager: Can't load icons from iconset.";
    }

    // add icons from path
    renderIcons();
}

bool IconManager::createCache()
{

    QString iconSubdir(m_iconSets[m_activeSetBasename].path);
    QString iconSetPath(QString("%1%2%3").arg(DirPathsManager::instance().iconDir(), iconSubdir, ".xml"));
    QDomDocument document;

    if(!readXMLFile(iconSetPath, document, "xml")) return false;

    QDomElement documentElement = document.documentElement();
    QDomNodeList elements = documentElement.elementsByTagName( tagIcon );

    for (int i=0; i<elements.length(); i++) {

        QDomElement icon = elements.at(i).toElement();

        QString iconPath = QString("%1%2%3").arg(DirPathsManager::instance().iconDir(), iconSubdir, "/" + icon.attribute("file"));
        QString iconName = icon.attribute("id");
        QColor iconColor = baseColor();

        if (m_pxCache.contains(iconName))
            continue;

        // if defined, override icon base color with color from iconset
        if(m_forDarkMode && icon.hasAttribute(colorOnDark)){
            iconColor = ThemeManager::instance().parseColor(icon.attribute(colorOnDark));
        }else if(!m_forDarkMode && icon.hasAttribute(colorOnLight)){
            iconColor = ThemeManager::instance().parseColor(icon.attribute(colorOnLight));
        }

        m_pxCache.insert(iconName, loadPixmap(iconPath, iconColor));

    }

    return true;

}

void IconManager::renderIcons()
{

    QMapIterator<QString, QPainterPath*> i(m_iconPaths);
    while (i.hasNext()) {
        i.next();
        if (!m_pxCache.contains(i.key())){
            m_pxCache.insert(i.key(), renderPath(*i.value()));
        }
    }


}

void IconManager::applyColors(QDomDocument &doc, QString fileName, QColor color)
{

    QDomElement rootElement = doc.documentElement();

    // Add "dark" selector to root node
    if(m_forDarkMode) rootElement.setAttribute("class", classDark);

    // Set icon base color if not already set
    if(!rootElement.hasAttribute("fill")){
        QColor iconBaseColor = (color.isValid()) ? color : baseColor();
        QString baseColor = "rgb(" + QString::number(iconBaseColor.red()) + "," + QString::number(iconBaseColor.green()) + "," + QString::number(iconBaseColor.blue()) + ")";
        rootElement.setAttribute("fill", baseColor);
    }


    QDomNode n = rootElement.firstChild();

    QMap<QString, QString> *styles = new QMap<QString, QString>();



    // iterate all nodes
    while(!n.isNull()) {
        QDomElement e = n.toElement();
        if(!e.isNull()) {

            if(e.nodeName() == "style"){
                //                 qDebug() << e.tagName() << '\n';
                //                 qDebug() << e.childNodes().at(0).toText().data() << '\n';

                QString styleImport = e.childNodes().at(0).toText().data();

                QRegularExpression rx_css("(.*?@import.*?')(.*?)('.*)");
                QRegularExpressionMatch mImport = rx_css.match(styleImport);

                // Check if stylesheet import is available
                if (mImport.hasMatch()) {

                    QString cssFile = mImport.captured(2).trimmed();
                    QString absFile = QDir::cleanPath(QFileInfo(fileName).absoluteDir().absolutePath() + "/" + cssFile);

                    // Check if css file exists and add content to node
                    QFile fileCSS(absFile);
                    if(fileCSS.exists()){

                        fileCSS.open(QIODevice::ReadOnly);
                        QByteArray baData = fileCSS.readAll();

                        QString styleSheet = QString(baData);

                        // ISSUE: QSvgRenderer can't apply styles to a <path> item with evenodd path
                        // SOLUTION: we use our own parser and add inline styles to each tag
                        // append content of css file to style tag
                        //e.childNodes().at(0).setNodeValue(styleSheet);

                        // Parse Style Sheet
                        styles = parseStyleSheet(styleSheet);

                    }else{
                        qWarning() << "IconManager: Couldn't load CSS file for icon style! [" << fileName << "]";
                    }

                }

            }

            // add style of imported stylesheet as inline styles to each corresponding tag
            // It is a workaround for even odd shapes in QSvgRenderer
            if(e.hasAttribute("class")){

                QString darClass = (m_forDarkMode) ? "." + classDark : "";
                QString style = styles->value(darClass + "." + e.attribute("class"));

                if(!style.isEmpty()){
                    e.setAttribute("style", style );
                }

            }


            //            if(e.nodeName() == "g") e.setAttribute("class", classBase);
            //            if(e.nodeName() == "path") e.setAttribute("class", classBase);

        }
        n = n.nextSibling();
    }
}

QMap<QString, QString> *IconManager::parseStyleSheet(QString styleString)
{
    QMap<QString, QString> *styles = new QMap<QString, QString>;

    if (styleString.isEmpty()) {
        qDebug("IconManager::parseStyleSheet: Style string is empty!");
        return styles;
    }

    // Remove C-style comments /* */ or // from stylesheet
    QRegularExpression rx_comments("(\\/\\*[\\s\\S]*?(.*?)\\*\\/)|(\\/\\/.*)");
    styleString.remove(rx_comments);


    // Group 1: tags, like ".onDark .success"
    // Group 2: strings within {}
    QRegularExpression rx_Settings("(.*?)\\s*{([^\\}]+)}");
    QRegularExpressionMatchIterator i = rx_Settings.globalMatch(styleString);


    while (i.hasNext()) {
        QRegularExpressionMatch mStyle = i.next();

        styles->insert(mStyle.captured(1).trimmed().replace(" ", ""), mStyle.captured(2).trimmed());
    }

   return styles;
}



QPixmap *IconManager::loadPixmap(const QString filePath, QColor color)
{

    QDomDocument document;

    // Load SVG file
    if(readXMLFile(filePath, document, "svg")){

        // process style from css file
        applyColors(document, filePath, color);

        QSvgRenderer svgRenderer(document.toByteArray());

        QPixmap *iconPixmap = new QPixmap(svgRenderer.defaultSize());
        iconPixmap->fill(Qt::transparent);

        QPainter painter(iconPixmap);
        svgRenderer.render(&painter);
        painter.end();

        return iconPixmap;
    }
    // Load any other file format
    else{
        return new QPixmap(filePath);
    }
}

QPixmap *IconManager::renderPath(QPainterPath path)
{
    QSize size(path.boundingRect().width(), path.boundingRect().height());
    QPixmap pixmap(size);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(baseColor()));
    painter.setPen(Qt::NoPen);
    painter.drawPath(path);
    painter.end();

    return new QPixmap(pixmap);

}

bool IconManager::readXMLFile(QString filePath, QDomDocument &document, QString fileExtenstion)
{

//    QFileInfo file(filePath);
//    QFile dataFile(file.absoluteFilePath());
//    if (!dataFile.exists())
//        return false;
//    if (!dataFile.open(QIODevice::ReadOnly))
//        return false;
//    QTextStream ts(&dataFile);
//    ts.setEncoding(QStringConverter::Utf8); // --> Qt6
//    //ts.setCodec(QTextCodec::codecForName("UTF-8")); // --> Qt5
//    QString errorMsg;
//    int eline;
//    int ecol;
//    document = QDomDocument( QString(file.baseName()));
//    QString data(ts.readAll());
//    dataFile.close();

//    if (!document.setContent( data, &errorMsg, &eline, &ecol))
//    {
//        qDebug()<<data<<errorMsg<<eline<<ecol;
//        if (data.contains("404 not found", Qt::CaseInsensitive))
//            qDebug()<<"File not found on server";
//        else
//            qDebug()<<"Could not open file"<<dataFile.fileName();
//        return false;
//    }

//    return true;

        QFileInfo fileInfo(filePath);
        if(fileInfo.completeSuffix() != fileExtenstion) return false;


        QFile inFile( filePath );
        if( !inFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
        {
            qWarning() << "IconManager: Failed to open file '" + filePath + "' for reading.";
            return false;
        }

        if( !document.setContent( &inFile ) )
        {
            qWarning() << "IconManager: Failed to parse the file '" + filePath + "'into a DOM tree.";
            inFile.close();
            return false;
        }

        inFile.close();
        return true;
}

//void IconManager::tintPixmap(QPixmap &pixmap, QColor color)
//{
//    //QPixmap pm = pixmap;
//    QPainter painter(&pixmap);
//    painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
//    painter.fillRect(pixmap.rect(), color);
//    painter.end();
//}



bool IconManager::initIconSets()
{
    readIconConfigFiles();
    return !(m_iconSets.isEmpty() || m_activeSetBasename.isEmpty());
}

void IconManager::readIconConfigFiles()
{
    QString baseIconDir(DirPathsManager::instance().iconDir());
    QStringList locations;
    locations << baseIconDir;

    for (QStringList::Iterator it = locations.begin(); it != locations.end(); ++it)
    {
        QFileInfo iconDir(*it);
        if (!iconDir.exists())
            continue;

        QDir id(*it, "*.xml", QDir::Name, QDir::Dirs | QDir::NoDotAndDotDot | QDir::Files | QDir::NoSymLinks);
        if (!id.exists() || (id.count() == 0))
            continue;

        // Read all iconset files
        for (uint i = 0; i < id.count(); ++i)
        {

            QFileInfo file(*it + id[i]);
            //qDebug()<<file.absoluteFilePath();
            QDomDocument xmlData;

            if(!readXMLFile(file.absoluteFilePath(), xmlData, "xml")) continue;

            QDomElement docElem = xmlData.documentElement();
            IconSetData isd;
            for (QDomNode n = docElem.firstChild(); !n.isNull(); n = n.nextSibling())
            {
                QDomElement e = n.toElement();
                if (e.isNull())
                    continue;

                //qDebug()<<e.tagName()<<e.text();
                if (e.tagName() == "path")
                {
                    isd.path = e.text();

                    if (e.hasAttribute("default"))
                    {
                        isd.isDefault = (e.attribute("default") == "yes") ?  true : false;
                    } else isd.isDefault = false;
                }
                else if (e.tagName() == "author")
                {
                    isd.author = e.text();
                }
                else if (e.tagName() == "license")
                {
                    isd.license = e.text();
                }
                else if (e.tagName() == "activeversion")
                {
                    isd.activeversion = e.text();
                }
                else if (e.tagName() == "nametext")
                {
                    if (e.hasAttribute("lang"))
                    {
                        isd.nameTranslations.insert(e.attribute("lang"),e.text());
                        if (e.attribute("lang") == "en_US")
                            isd.baseName = e.text();
                    }
                }

            }

            //just in case there's no en_US basename
            if (isd.baseName.isEmpty())
                continue;

            // Add iconset to list of available iconsets
            m_iconSets.insert(isd.baseName, isd);

            if (isd.activeversion.isEmpty())
                continue;

            int av_major = isd.activeversion.section(".", 0, 0).toInt();
            int av_minor = isd.activeversion.section(".", 1, 1).toInt();
            int av_patch = isd.activeversion.section(".", 2, 2).toInt();
            int av_fullver = av_major * 10000 + av_minor * 100 + av_patch;

            int curr_major = m_activeSetVersion.section(".", 0, 0).toInt();
            int curr_minor = m_activeSetVersion.section(".", 1, 1).toInt();
            int curr_patch = m_activeSetVersion.section(".", 2, 2).toInt();
            int curr_fullver = curr_major * 10000 + curr_minor * 100 + curr_patch;

            int ver_major = ScribusAPI::getVersionMajor();
            int ver_minor = ScribusAPI::getVersionMinor();
            int ver_patch = ScribusAPI::getVersionPatch();
            int ver_fullver = ver_major * 10000 + ver_minor * 100 + ver_patch;

            //If iconset version <= app version, and iconset version >= current active iconset version
            if ((av_fullver <= ver_fullver) && (av_fullver >= curr_fullver))
            {
                //                if (av_fullver == curr_fullver)
                //                    continue;

                if(!isd.isDefault)
                    continue;

                m_backupSetBasename = m_activeSetBasename;
                m_activeSetBasename = isd.baseName;
                m_activeSetVersion = isd.activeversion;
            }
        }
    }
}




