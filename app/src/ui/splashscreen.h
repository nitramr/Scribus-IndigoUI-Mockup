#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QSplashScreen>

class SplashScreen : public QSplashScreen
{
public:
    SplashScreen();

    void showStatusMessage(const QString &message, QColor colorOnDark = Qt::white, QColor colorOnLight = Qt::black);
    void setMessageRect(QRect rect, int alignement);

    virtual void drawContents(QPainter *painter);

private:
    QString message;
    int alignement;
    QColor colorText;
    QRect rect;
    bool isDark;

};

#endif // SPLASHSCREEN_H
