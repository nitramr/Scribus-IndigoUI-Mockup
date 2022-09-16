#ifndef FORMWIDGET_H
#define FORMWIDGET_H

#include <QWidget>
#include <QFont>

class FormWidget : public QWidget
{
    Q_OBJECT
    Q_CLASSINFO("Version", "1.0.0")

    Q_PROPERTY(QString label READ label WRITE setLabel)
    Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap)
    Q_PROPERTY(QSize pixmapSize READ pixmapSize WRITE setPixmapSize)
    Q_PROPERTY(LabelPosition direction READ direction WRITE setDirection)
    Q_PROPERTY(QFont font READ font WRITE setFont STORED true)
    Q_PROPERTY(int space READ space WRITE setSpace)
    Q_PROPERTY(bool preserveLabelSpace READ preserveLabelSpace WRITE setPreserveLabelSpace)


public:

    enum LabelPosition { Left, Top, Right, Bottom };
    Q_ENUM(LabelPosition)

    explicit FormWidget(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;

    void setLabel(QString const &text);
    QString label();

    void setPreserveLabelSpace(bool preserveSpace);
    bool preserveLabelSpace();

    void setDirection(FormWidget::LabelPosition direction);
    FormWidget::LabelPosition direction();

    void setFont(QFont font);
    QFont font();

    void setSpace(int space);
    int space();

    void setPixmap(QPixmap icon);
    QPixmap pixmap();

    void setPixmapSize(QSize size);
    QSize pixmapSize();

    bool hasPixmap() const;

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private:
    LabelPosition m_position;
    int m_space;
    QSize m_pixmapSize;
    QString m_label;
    QFont m_font;
    QPixmap m_pixmap;
    bool m_preserveLabelSpace;

    void calculateFrame();
    void labelSize(int &w, int &h) const;
};


#endif
