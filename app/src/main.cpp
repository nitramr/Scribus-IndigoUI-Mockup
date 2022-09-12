#include "mainwindow.h"

#include <QStyleFactory>
#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "configuration_manager.h"
#include "file_utils.h"
#include "splashscreen.h"
#include <QTimer>

int main(int argc, char *argv[])
{

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

    QApplication app(argc, argv);

//    QTranslator translator;
//    const QStringList uiLanguages = QLocale::system().uiLanguages();
//    for (const QString &locale : uiLanguages) {
//        const QString baseName = "Scribus-IndigoUI_" + QLocale(locale).name();
//        if (translator.load(":/i18n/" + baseName)) {
//            app.installTranslator(&translator);
//            break;
//        }
//    }

    // Fusion looks better in general, but feel free to change
    //    qApp->setStyle(QStyleFactory::create(QStringLiteral("Fusion")));


    SplashScreen splash;
    splash.setMessageRect( QRect(15, 97, 460-16, 320-16), Qt::AlignBottom | Qt::AlignRight );
    splash.showStatusMessage( "Loading...", QColor(207, 215,222), QColor(53, 79, 105) );
    splash.show();

    QApplication::processEvents();

    MainWindow w;
    w.showMaximized();
//    splash.finish(&w);
    QTimer::singleShot(2000, &splash, &QWidget::close); // keep displayed for 3 seconds

    return app.exec();
}
