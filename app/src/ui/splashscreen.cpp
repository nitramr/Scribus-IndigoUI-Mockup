#include "splashscreen.h"
#include <QPainter>
#include "theme_manager.h"

SplashScreen::SplashScreen()
{

    ThemeManager &themeManager = ThemeManager::instance();
    themeManager.setup();
    isDark = themeManager.isDark();
    QString splashImage = (isDark) ? ":/images/splashscreen_dark" : ":/images/splashscreen_light";

    this->setPixmap(QPixmap(splashImage));
    this->setWindowFlag(Qt::WindowStaysOnTopHint, true);

}

void SplashScreen::showStatusMessage(const QString &message, QColor colorOnDark, QColor colorOnLight)
{
    this->message = message;
    this->colorText = isDark ? colorOnDark : colorOnLight;
    this->showMessage(this->message, this->alignement, this->colorText);
}

void SplashScreen::setMessageRect(QRect rect, int alignement)
{
    this->rect = rect;
    this->alignement = alignement;
}

void SplashScreen::drawContents(QPainter *painter)
{
    QPixmap textPix = QSplashScreen::pixmap();
    painter->setPen(this->colorText);
    painter->drawText(this->rect, this->alignement, this->message);
}
