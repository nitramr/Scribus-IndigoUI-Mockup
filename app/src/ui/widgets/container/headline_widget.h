#ifndef HEADLINEWIDGET_H
#define HEADLINEWIDGET_H

#include <QWidget>
#include <QLabel>



class HeadlineWidget : public QWidget
{
    Q_OBJECT
    Q_CLASSINFO("Version", "1.0.0")

    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(FontSize fontSize READ fontSize WRITE setFontSize DESIGNABLE true)
    Q_PROPERTY(bool lineVisibile READ lineVisible WRITE setLineVisible)

public:

    enum FontSize{
        Normal = 0,
        H1 = 1,
        H2 = 2,
        H3 = 3
    };
    Q_ENUM(FontSize)

    explicit HeadlineWidget(const QString text, FontSize fontSize = FontSize::H3, QWidget *parent = nullptr);
    HeadlineWidget(QWidget *parent = nullptr);

    const QString text();
    void setText(const QString text);

    FontSize fontSize();
    void setFontSize(FontSize size);

    bool lineVisible();
    void setLineVisible(bool visible);

private:
    QLabel *m_label;
    QFrame * m_line;
    FontSize m_fontSize;

signals:

};

#endif // HEADLINEWIDGET_H
