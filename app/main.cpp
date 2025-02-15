#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDir>
#include "iwindow.h"
#include "pluginmanager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon.png"));
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "app_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    PluginManager pluginManager;
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cdUp();
    pluginsDir.cd("plugins");

    QString pluginFilter;
#ifdef Q_OS_WINDOWS
    pluginFilter = "*.dll";
#elif defined(Q_OS_LINUX)
    pluginFilter = "*.so";
#endif


    QFileInfoList plugins = pluginsDir.entryInfoList({pluginFilter}, QDir::Files);

    PluginManager::addPlugins(plugins);
    PluginManager::loadPlugins();
    IWindow::showWindow();
    return a.exec();
}
