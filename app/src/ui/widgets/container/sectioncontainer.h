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
    Q_PROPERTY(bool hasStyle READ hasStyle WRITE setHasStyle)


public:
    SectionContainer(QWidget *parent = nullptr);
    SectionContainer(QString title, bool isCollapsible = true, QWidget *parent = nullptr);

    void addHeaderSuffixWidget(QWidget *widget);
    void insertHeaderSuffixWidget(int index, QWidget *widget);    
    void removeHeaderSuffixWidget(QWidget *widget);
    void addHeaderSuffixSpacing(int size);
    void insertHeaderSuffixSpacing(int index, int size);

    void addHeaderPrefixWidget(QWidget *widget);
    void insertHeaderPrefixWidget(int index, QWidget *widget);
    void removeHeaderPrefixWidget(QWidget *widget);
    void addHeaderPrefixSpacing(int size);
    void insertHeaderPrefixSpacing(int index, int size);


    void setText(QString text);
    QString text() const;

    void setFont(QFont font);
    QFont font();

    void setHasStyle(bool hasStyle);
    bool hasStyle();

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
    QHBoxLayout * layoutHeaderPrefix;
    QHBoxLayout * layoutHeaderSuffix;
    QStackedWidget * bodyWidget;
    QLabel * labelTitle;
    QToolButton * buttonCollapse;
    QWidget * headerWidget;
    QIcon iconCollapsed;
    QIcon iconExpanded;
    bool boolIsCollapsible;
    bool boolIsCollapsed;
    QSizePolicy tmpSizePolicy;
    bool boolHasStyle;

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
