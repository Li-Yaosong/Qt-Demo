#include "pluginmanager.h"

#include <QCoreApplication>
#include <QMutex>
#include <QDebug>
#include <QDir>
#include <QTimer>
#include "iplugin.h"
#include "plugintree.h"
InstancePtr(PluginManager)
class PluginManagerPrivate : public QObject
{
public:
    PluginManagerPrivate(PluginManager *pluginManager)
        :m_pluginManager(pluginManager),
        m_pluginTreeModel(new PluginTreeModel)
    {
        Q_UNUSED(m_pluginManager);
        qInstallMessageHandler(PluginManagerPrivate::messageHandler);
    }
    ~PluginManagerPrivate()
    {
        qInstallMessageHandler(nullptr);
        qDebug() << "PluginManagerPrivate destructor";
        if (m_pluginTreeModel) {
            m_pluginTreeModel->deleteLater();
        }
    }
    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
    {
        Q_UNUSED(context);
        QString time = QDateTime::currentDateTime().toString("yyyy.MM.dd HH:mm:ss");
        static QMutex mutex;
        QMutexLocker locker(&mutex);

        QString logLevel;
        QString color;
        switch (type)
        {
        case QtDebugMsg:
            logLevel = "DEBUG";
            color = "black";
            break;
        case QtInfoMsg:
            logLevel = "INFO";
            color = "blue";
            break;
        case QtWarningMsg:
            logLevel = "WARNING";
            color = "orange";
            break;
        case QtCriticalMsg:
            logLevel = "CRITICAL";
            color = "red";
            break;
        case QtFatalMsg:
            logLevel = "FATAL";
            color = "darkred";
            break;
        }
        QString fromat("<span style='color:%1;'>[%2] [%3] %4 %5</span>");
        PluginManager::instance()->m_p->previousMessages.append(context.category + QString(" " + msg));
        emit PluginManager::instance()->outputMessage(fromat.arg(color, time, logLevel, context.category, msg));
    }

    PluginTreeModel *pluginTreeModel()
    {
        return m_pluginTreeModel;
    }
    void loadPlugin(IPluginLoader *pluginInfo)
    {
        if (!pluginInfo) {
            return;
        }
        QVariantList dependencies = pluginInfo->dependencies();
        if(dependencies.isEmpty()) {
            initializePlugin(pluginInfo);
        }
        else
        {
            for(const QVariant &dep : std::as_const(dependencies))
            {
                loadPlugin(pluginMap.value(dep.toString()));
            }
            initializePlugin(pluginInfo);
        }
        pluginInfo->setInitialized(true);
        emit m_pluginManager->pluginLoaded(pluginInfo);
    }

    void initializePlugin(IPluginLoader *pluginLoader)
    {

        if (pluginLoader) {
            qInfo() << pluginLoader->name();
            QObject *plugin = pluginLoader->instance();
            if (plugin && !pluginLoader->initialized()) {
                QString err;
                qobject_cast<IPlugin *>(plugin)->initialize({pluginLoader->fileName()}, &err);
            }
        }
    }
    QMap<QString, IPluginLoader *> pluginMap;
    friend class PluginManager;
private:
    QStringList previousMessages;
    PluginManager *m_pluginManager = nullptr;
    PluginTreeModel *m_pluginTreeModel = nullptr;
};
void PluginManager::addPlugins(const QFileInfoList &plugins)
{
    for (const QFileInfo &fileInfo : plugins) {
        IPluginLoader *pluginLoader = new IPluginLoader(fileInfo.absoluteFilePath());
        instance()->m_p->pluginTreeModel()->addPlugin(pluginLoader);
        instance()->m_p->pluginMap.insert(pluginLoader->name(), pluginLoader);
    }
}

PluginManager::PluginManager():
    m_p(new PluginManagerPrivate(this))
{
}

PluginManager::~PluginManager()
{
    delete m_p;
}
void PluginManager::loadPlugins()
{
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cdUp();
    pluginsDir.cd("plugins");

    QString pluginFilter;
#ifdef Q_OS_WINDOWS
    pluginFilter = "*.dll";
#elif defined(Q_OS_LINUX)
    pluginFilter = "*.so";
#endif
    PluginManager::addPlugins(pluginsDir.entryInfoList({pluginFilter}, QDir::Files));
    /*
     * 按加载顺序加载插件
     */
    QVector<IPluginLoader *> plugins = instance()->m_p->pluginTreeModel()->m_plugins;
    for (IPluginLoader *pluginInfo : std::as_const(plugins)) {
        instance()->m_p->loadPlugin(pluginInfo);
    }
    emit instance()->pluginsLoaded();
}

const PluginTreeModel *PluginManager::pluginTreeModel()
{
    return instance()->m_p->pluginTreeModel();
}

QStringList PluginManager::previousMessages()
{
    return m_p->previousMessages;
}



