#include "iapplication.h"
#include "pluginmanager.h"

#include <QTranslator>
#include "iwindow.h"
class IApplicationPrivate
{
public:
    IApplicationPrivate(int &argc, char **argv)
        :argc(argc),
        argv(argv),
        pluginManager(PluginManager::instance())
    {

    };
    ~IApplicationPrivate()
    {
        IWindow::deleteInstance();
    };
    int argc;
    char **argv;
    PluginManager *pluginManager = nullptr;
    IWindow *window = nullptr;
};
IApplication::IApplication(int &argc, char **argv)
    :QObject{},
    d_ptr(new IApplicationPrivate(argc, argv))
{
    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL, false);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
#endif
}

void IApplication::qtDebugPlugins(bool enabled)
{
    qputenv("QT_DEBUG_PLUGINS", enabled ? "1" : "0");
}

int IApplication::exec()
{
    if (!QApplication::instance())
    {
        connect(this, &IApplication::appCreated, d_ptr->pluginManager, &PluginManager::loadPlugins,
                Qt::SingleShotConnection);
        static  QApplication app(d_ptr->argc, d_ptr->argv);
        connect(&app, &QApplication::aboutToQuit, d_ptr->pluginManager, &PluginManager::deleteInstance);
        d_ptr->window = IWindow::instance();
        connect(d_ptr->pluginManager, &PluginManager::pluginsLoaded, d_ptr->window, &IWindow::show,
                Qt::SingleShotConnection);

        emit IApplication::appCreated();
    }
    qApp->setWindowIcon(QIcon(":/icon.png"));

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "app_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            qApp->installTranslator(&translator);
            break;
        }
    }
    return qApp->exec();
}

IApplication::~IApplication()
{
    delete d_ptr;
}
