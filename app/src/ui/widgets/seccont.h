#ifndef SECCONT_H
#define SECCONT_H

#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QComboBox;
class QStackedWidget;
QT_END_NAMESPACE


class SectionContainer : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)

    Q_PROPERTY(QString title READ text WRITE setText)

public:
    explicit SectionContainer(QWidget *parent = nullptr);

    QSize sizeHint() const override;

    int count() const;
    int currentIndex() const;
    QWidget *widget(int index);

    void setText(QString text);
    QString text() const;

    void setIsCollapsible(bool isCollapsible);
    bool isCollapsible();
    bool isCollapsed();


public slots:
    void addPage(QWidget *page);
    void insertPage(int index, QWidget *page);
    void removePage(int index);
    void setCurrentIndex(int index);

    void toggleCollpasedState();
    void setIsCollapsed(bool state);

signals:
    void currentIndexChanged(int index);
    void collapsedState(bool);

private:
    QStackedWidget *stackWidget;
    QLabel * labelTitle;
    QToolButton * buttonCollapse;
    QWidget * headerWidget;
    QHBoxLayout * addonLayout;

    bool boolIsCollapsible;
    bool boolIsCollapsed;

    void connectSlots();
};


#endif
