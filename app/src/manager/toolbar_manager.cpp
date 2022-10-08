#include "toolbar_manager.h"
#include "icon_manager.h"
#include "mainwindow.h"

#include <QLabel>
#include <QToolButton>


ToolbarManager* ToolbarManager::m_instance = nullptr;

/* ********************************************************************************* *
 *
 * Constructor + Setup
 *
 * ********************************************************************************* */

ToolbarManager::ToolbarManager(QObject *parent)
    : QObject(parent)
{



}


void ToolbarManager::setup(MainWindow *mainWindow)
{
    m_mainWindow = mainWindow;

    m_toolTools = new QToolBar();
    m_toolQuickTools = new ToolBarQuickTools();
    m_toolArcProperties = new ToolBarPropertyArc();
    m_toolEmptyProperties = new ToolBarPropertyEmpty();
    m_toolBezierProperties = new ToolBarPropertyBezier();
    m_toolTableProperties = new ToolBarPropertyTable();
    m_toolPolygonProperties = new ToolBarPropertyPolygon();
    m_toolSpiralProperties = new ToolBarPropertySpiral();
    m_toolMeasurementProperties = new ToolBarPropertyMeasurement();
    m_toolCalligraphyProperties = new ToolBarPropertyCalligraphy();
    m_toolGradientProperties = new ToolBarPropertyGradient();

    initTools();
    initQuickTools();
    initToolEmptyProperties();
    initToolArcProperties();
    initToolBezierProperties();
    initToolTableProperties();
    initToolPolygonProperties();
    initToolSpiralProperties();
    initToolMeasurementProperties();
    initToolCalligraphyProperties();
    initToolGradientProperties();

}


void ToolbarManager::initTools()
{

    // Toolbar settings
    m_toolTools->setOrientation(Qt::Vertical);
    m_toolTools->setToolButtonStyle(Qt::ToolButtonIconOnly);
    m_toolTools->setIconSize(QSize(24,24));
    m_toolTools->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea | Qt::BottomToolBarArea);

    // Selection
    m_toolTools->addAction( actionTool("tool-selection",            tr("Selection"), Tool::None) );
    m_toolTools->addAction( actionTool("tool-edit",                 tr("Edit"), Tool::Bezier) );
    m_toolTools->addSeparator();
    // Content
    m_toolTools->addAction( actionTool("tool-text-frame",           tr("Textbox"), Tool::None) );
    m_toolTools->addAction( actionTool("tool-image",                tr("Image"), Tool::None) );
    m_toolTools->addAction( actionTool("tool-render-frame",         tr("Render Frame"), Tool::None) );
    m_toolTools->addAction( actionTool("tool-table",                tr("Table"), Tool::Table) );
    m_toolTools->addSeparator();
    // Path + Shapes
    m_toolTools->addAction( actionTool("tool-rectangle",            tr("Rectangle"), Tool::None) );
    m_toolTools->addAction( actionTool("tool-star",                 tr("Star"), Tool::Polygon) );
    m_toolTools->addAction( actionTool("tool-arc",                  tr("Arc"), Tool::Arc) );
    m_toolTools->addAction( actionTool("tool-spiral",               tr("Spiral"), Tool::Spiral) );
    m_toolTools->addAction( actionTool("tool-line",                 tr("Line"), Tool::None) );
    m_toolTools->addAction( actionTool("tool-bezier",               tr("Bezier"), Tool::None) );
    m_toolTools->addAction( actionTool("tool-pencil",               tr("Pen"), Tool::None) );
    m_toolTools->addAction( actionTool("tool-calligraphy",          tr("Calligraphy"), Tool::Calligraphy) );
    m_toolTools->addSeparator();
    // Tools
    m_toolTools->addAction( actionTool("tool-gradient",             tr("Gradient Edit"), Tool::Gradient) );
    m_toolTools->addAction( actionTool("tool-rotate",               tr("Rotate"), Tool::None) );
    m_toolTools->addAction( actionTool("tool-zoom",                 tr("Zoom"), Tool::None) );
    m_toolTools->addAction( actionTool("tool-text-link",            tr("Link Text Frames"), Tool::None) );
    m_toolTools->addAction( actionTool("tool-text-unlink",          tr("Unlink Text Frames"), Tool::None) );
    m_toolTools->addAction( actionTool("tool-measure",              tr("Measure"), Tool::Measurement) );
    m_toolTools->addAction( actionTool("tool-property-copy",        tr("Copy Item property"), Tool::None) );
    m_toolTools->addAction( actionTool("tool-eyedropper",           tr("Eye Dropper"), Tool::None) );
    m_toolTools->addSeparator();
    // Plugins
    m_toolTools->addAction( actionTool("tool-barcode",              tr("Barcode"), Tool::None) );
}

void ToolbarManager::initQuickTools()
{

    m_toolQuickTools->setMovable(false);
    m_toolQuickTools->setFloatable(false);
    m_toolQuickTools->setOrientation(Qt::Horizontal);
    m_toolQuickTools->setAllowedAreas(Qt::TopToolBarArea);


}

void ToolbarManager::initToolEmptyProperties()
{
    m_toolEmptyProperties->setVisible(true);
}

void ToolbarManager::initToolArcProperties()
{
    m_toolArcProperties->setVisible(false);
}

void ToolbarManager::initToolBezierProperties()
{
    m_toolBezierProperties->setVisible(false);
}

void ToolbarManager::initToolTableProperties()
{
    m_toolTableProperties->setVisible(false);
}

void ToolbarManager::initToolPolygonProperties()
{
    m_toolPolygonProperties->setVisible(false);
}

void ToolbarManager::initToolSpiralProperties()
{
    m_toolSpiralProperties->setVisible(false);
}

void ToolbarManager::initToolMeasurementProperties()
{
    m_toolMeasurementProperties->setVisible(false);
}

void ToolbarManager::initToolCalligraphyProperties()
{
    m_toolCalligraphyProperties->setVisible(false);
}

void ToolbarManager::initToolGradientProperties()
{
    m_toolGradientProperties->setVisible(false);
}

/* ********************************************************************************* *
 *
 * Private Members
 *
 * ********************************************************************************* */

QAction *ToolbarManager::actionTool(QString icon, QString label, Tool data)
{
    QAction *action = new QAction(IconManager::instance().icon(icon), label);
    action->setData(data);
    connect(action, &QAction::triggered, this, &ToolbarManager::togglePropertyToolBar);
    connect(action, &QAction::triggered, m_mainWindow, &MainWindow::dummySlot);

    return action;
}

/* ********************************************************************************* *
 *
 * Public Members
 *
 * ********************************************************************************* */

ToolbarManager &ToolbarManager::instance()
{
    static ToolbarManager m_instance;
    return m_instance;
}

QToolBar *ToolbarManager::toolbarTools()
{
    return m_toolTools;
}

ToolBarQuickTools *ToolbarManager::toolbarQuickTools()
{
    return m_toolQuickTools;
}

ToolBarPropertyEmpty *ToolbarManager::toolbarEmptyProperties()
{
    return m_toolEmptyProperties;
}

ToolBarPropertyArc *ToolbarManager::toolbarArcProperties()
{
    return m_toolArcProperties;
}

ToolBarPropertyBezier *ToolbarManager::toolbarBezierProperties()
{
    return m_toolBezierProperties;
}

ToolBarPropertyTable *ToolbarManager::toolbarTableProperties()
{
    return m_toolTableProperties;
}

ToolBarPropertyPolygon *ToolbarManager::toolbarPolygonProperties()
{
    return m_toolPolygonProperties;
}

ToolBarPropertySpiral *ToolbarManager::toolbarSpiralProperties()
{
    return m_toolSpiralProperties;
}

ToolBarPropertyMeasurement *ToolbarManager::toolbarMeasurementProperties()
{
    return m_toolMeasurementProperties;
}

ToolBarPropertyCalligraphy *ToolbarManager::toolbarCalligraphyProperties()
{
    return m_toolCalligraphyProperties;
}

ToolBarPropertyGradient *ToolbarManager::toolbarGradientProperties()
{
    return m_toolGradientProperties;
}


/* ********************************************************************************* *
 *
 * Private Slots
 *
 * ********************************************************************************* */

void ToolbarManager::togglePropertyToolBar()
{

    QAction *action = qobject_cast<QAction *>(sender());

    if(action != nullptr){

        m_toolEmptyProperties->setVisible(false);
        m_toolArcProperties->setVisible(false);
        m_toolBezierProperties->setVisible(false);
        m_toolTableProperties->setVisible(false);
        m_toolPolygonProperties->setVisible(false);
        m_toolSpiralProperties->setVisible(false);
        m_toolMeasurementProperties->setVisible(false);
        m_toolCalligraphyProperties->setVisible(false);
        m_toolGradientProperties->setVisible(false);

        Tool m_tool = static_cast<ToolbarManager::Tool>(action->data().toInt());

//        qDebug() << "Selected tool is" << m_tool;

        switch(m_tool){
        default:
        case Tool::None:
            m_toolEmptyProperties->setVisible(true);
            break;
        case Tool::Arc:
            m_toolArcProperties->setVisible(true);
            break;
        case Tool::Bezier:
            m_toolBezierProperties->setVisible(true);
            break;
        case Tool::Table:
            m_toolTableProperties->setVisible(true);
            break;
        case Tool::Polygon:
            m_toolPolygonProperties->setVisible(true);
            break;
        case Tool::Spiral:
            m_toolSpiralProperties->setVisible(true);
            break;
        case Tool::Measurement:
            m_toolMeasurementProperties->setVisible(true);
            break;
        case Tool::Calligraphy:
            m_toolCalligraphyProperties->setVisible(true);
            break;
        case Tool::Gradient:
            m_toolGradientProperties->setVisible(true);
            break;
        }

    }


}
