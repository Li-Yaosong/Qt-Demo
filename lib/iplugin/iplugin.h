#ifndef IPLUGIN_H
#define IPLUGIN_H

#include "iplugin_global.h"
#include <QObject>
class IPluginPrivate;
class IPLUGIN_EXPORT IPlugin : public QObject
{
    Q_OBJECT
    friend IPluginPrivate;
public:
    enum ShutdownFlag {
        SynchronousShutdown,
        AsynchronousShutdown
    };

    IPlugin() = default;
    ~IPlugin() = default;

    virtual bool initialize(const QStringList &arguments, QString *errorString);
    virtual void extensionsInitialized();
    virtual bool delayedInitialize();
    virtual ShutdownFlag aboutToShutdown();
    QString pluginPath();
protected:
    virtual void initialize() = 0;
#ifdef Q_OS_WINDOWS
    virtual void crashOutput();
#endif
private:
    IPluginPrivate * m_p = nullptr;
};

#define IPlugin_iid "Examples.Plugin.IPlugin"

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(IPlugin,IPlugin_iid)
QT_END_NAMESPACE

#endif // IPLUGIN_H
