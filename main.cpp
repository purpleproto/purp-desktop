#include "mainwindow.h"
#include "settingsmanager.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;

    SettingsManager::instance().init();

    a.setApplicationVersion(APP_VERSION);
    a.setOrganizationDomain("Purple Protocol");
    a.setApplicationName("PurP");
    a.setOrganizationDomain("github.com/purpleproto");

    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "purp-desktop_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return QCoreApplication::exec();
}
