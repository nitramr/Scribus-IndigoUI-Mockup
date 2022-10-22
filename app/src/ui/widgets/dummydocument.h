#ifndef DUMMYDOCUMENT_H
#define DUMMYDOCUMENT_H

#include <QObject>
#include <QWidget>

class ManagePagePropertiesDialog;

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

    void showManagePageDialog();

private:

    enum ContextMenuType {
        Document = 0,
        Paper = 1,
        Image = 2
    };

    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent*event);

    void connectSlots();

    bool m_grid {false};
    bool m_baseline {false};
    bool m_guide {false};

    ManagePagePropertiesDialog * dialogManagePageProperties;
    ContextMenuType m_contextMenuType;
    QMenu *contextImage;
    QMenu *contextPaper;

    QRect rectDocument();
    QRect rectImage();

private slots:
    void showContextMenu(const QPoint &pos);


signals:

};

#endif // DUMMYDOCUMENT_H
