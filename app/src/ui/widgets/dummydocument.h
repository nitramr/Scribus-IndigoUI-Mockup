#ifndef DUMMYDOCUMENT_H
#define DUMMYDOCUMENT_H

#include <QObject>
#include <QWidget>

class DummyDocument : public QWidget
{
    Q_OBJECT
public:
    explicit DummyDocument(QWidget *parent = nullptr);

public slots:

    void setGridVisibility(bool enable);
    void setBaselineVisibility(bool enable);
    void setGuideVisibility(bool enable);

    void toggleGridVisibility();
    void toggleBaselineVisibility();
    void toggleGuideVisibility();

private:
    void paintEvent(QPaintEvent*);

    bool m_grid {true};
    bool m_baseline {true};
    bool m_guide {true};
signals:

};

#endif // DUMMYDOCUMENT_H
