#include "mainwindow.h"

#include <QStyleFactory>
#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "configurationmanager.h"
#include "helper.h"
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

    QApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Scribus-IndigoUI_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    // Fusion looks better in general, but feel free to change
    //    qApp->setStyle(QStyleFactory::create(QStringLiteral("Fusion")));


    QSplashScreen splash(QPixmap(":/images/splashscreen"), Qt::WindowStaysOnTopHint);
    splash.show();
    splash.showMessage("Loading...", Qt::AlignBottom | Qt::AlignLeft, Qt::white);
    QTimer::singleShot(2000, &splash, &QWidget::close); // keep displayed for 5 seconds


    MainWindow w;
    w.showMaximized();
    //splash.finish(&w);

    return app.exec();
}
