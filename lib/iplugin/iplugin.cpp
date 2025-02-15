#include "iplugin.h"
#include <QDebug>
#ifdef Q_OS_WINDOWS
#include <windows.h>
#endif
#include <defstruct.h>
class IPluginPrivate
{
public:
    void initializeWin(IPlugin * p)
    {
#ifdef Q_OS_WINDOWS
        __try {
            p->initialize();
        }  __except (EXCEPTION_EXECUTE_HANDLER) {
            p->crashOutput();
        }
#endif
    }
    QString pluginPath;
};

bool IPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(errorString)
    m_p = new IPluginPrivate;
    if(!arguments.isEmpty())
    {
        m_p->pluginPath = arguments.first();
    }
    qDebug() << QT_FUNC_NAME << pluginPath();
#ifdef Q_OS_WINDOWS
    m_p->initializeWin(this);
#else
    initialize();
#endif
    return true;
}

void IPlugin::extensionsInitialized()
{

}

bool IPlugin::delayedInitialize()
{
    return false;
}

QString IPlugin::pluginPath()
{
    return m_p->pluginPath;
}
#ifdef Q_OS_WINDOWS
void IPlugin::crashOutput()
{
    qWarning() << QString("Plugin: %1 crashed!").arg(pluginPath());
}
#endif
IPlugin::ShutdownFlag IPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}
