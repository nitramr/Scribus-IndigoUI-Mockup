#ifndef TOOLBARMANAGER_H
#define TOOLBARMANAGER_H


#include <QObject>
#include <QToolBar>

#include "toolbarproperty_arc.h"
#include "toolbarproperty_bezier.h"
#include "toolbarproperty_empty.h"
#include "toolbarproperty_polygon.h"
#include "toolbarproperty_spiral.h"
#include "toolbarproperty_table.h"

class MainWindow;
class ToolbarManager: public QObject
{

    Q_OBJECT
public:

    enum Tool {
        None = 0,
        Bezier = 1,
        Polygon = 2,
        Spiral = 3,
        Arc = 4,
        Measurement = 5,
        Table = 6,
        Calligraphy = 7

    };

    ToolbarManager(ToolbarManager const&) = delete;
    void operator=(ToolbarManager const&) = delete;
    static ToolbarManager& instance();

    void setup(MainWindow * mainWindow);

    QToolBar * toolbarTools();
    QToolBar * toolbarQuickTools();
    ToolBarPropertyEmpty * toolbarEmptyProperties();
    ToolBarPropertyArc * toolbarArcProperties();
    ToolBarPropertyBezier * toolbarBezierProperties();
    ToolBarPropertyTable * toolbarTableProperties();
    ToolBarPropertyPolygon * toolbarPolygonProperties();
    ToolBarPropertySpiral * toolbarSpiralProperties();

private:


    ToolbarManager(QObject *parent = nullptr);
    ~ToolbarManager() = default;

    static ToolbarManager* m_instance;

    MainWindow * m_mainWindow;
    QToolBar * m_toolTools;
    QToolBar * m_toolQuickTools;
    ToolBarPropertyEmpty * m_toolEmptyProperties;
    ToolBarPropertyArc * m_toolArcProperties;
    ToolBarPropertyBezier * m_toolBezierProperties;
    ToolBarPropertyTable * m_toolTableProperties;
    ToolBarPropertyPolygon * m_toolPolygonProperties;
    ToolBarPropertySpiral * m_toolSpiralProperties;

    QAction * actionTool(QString icon, QString label, Tool data);

    void initTools();
    void initQuickTools();
    void initToolEmptyProperties();
    void initToolArcProperties();
    void initToolBezierProperties();
    void initToolTableProperties();
    void initToolPolygonProperties();
    void initToolSpiralProperties();

private slots:

    void togglePropertyToolBar();

};

#endif // TOOLBARMANAGER_H
