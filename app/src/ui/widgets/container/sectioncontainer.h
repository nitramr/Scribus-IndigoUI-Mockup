#ifndef SECTIONCONTAINER_H
#define SECTIONCONTAINER_H

#include <QLabel>
#include <QStackedWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

class SectionContainer : public QWidget
{
    Q_OBJECT
    Q_CLASSINFO("Version", "1.0.0")

    Q_PROPERTY(QString title READ text WRITE setText)
    Q_PROPERTY(bool isCollapsible READ isCollapsible WRITE setIsCollapsible)
    Q_PROPERTY(bool isCollapsed READ isCollapsed WRITE setIsCollapsed)


public:
    SectionContainer(QWidget *parent = nullptr);
    SectionContainer(QString title, bool isCollapsible = true, QWidget *parent = nullptr);

    void addHeaderWidget(QWidget *widget);
    void insertHeaderWidget(int index, QWidget *widget);    
    void removeHeaderWidget(QWidget *widget);
    void addHeaderSpacing(int size);
    void insertHeaderSpacing(int index, int size);


    void setText(QString text);
    QString text() const;

    void setIsCollapsible(bool isCollapsible);
    bool isCollapsible();
    bool isCollapsed();

    void setCollapseIcons(QIcon collapsed, QIcon expanded);

    QWidget *widget(int index);

    void addPage(QWidget * page);

    int count() const;
    int currentIndex() const;

private:
    QHBoxLayout * headerLayout;
    QHBoxLayout * addonLayout;
    QStackedWidget * bodyWidget;
    QLabel * labelTitle;
    QToolButton * buttonCollapse;
    QWidget * headerWidget;
    QIcon iconCollapsed;
    QIcon iconExpanded;
    bool boolIsCollapsible;
    bool boolIsCollapsed;
    QSizePolicy tmpSizePolicy;

    void connectSlots();

    void paintEvent(QPaintEvent *event);
    bool eventFilter(QObject *object, QEvent *event);

public slots:
    void toggleCollpasedState();
    void setIsCollapsed(bool state);

    void insertPage(int index, QWidget *page);
    void removePage(int index);
    void setCurrentIndex(int index);

signals:
    void collapsedState(bool);
    void currentIndexChanged(int index);


};

#endif // SECTIONCONTAINER_H
