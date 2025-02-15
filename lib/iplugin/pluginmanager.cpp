#include "defstruct.h"
#include "pluginmanager_p.h"
// #include <QPluginLoader>
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>
#include <QVBoxLayout>
#include "iplugin.h"

static PluginManager *m_instance = nullptr;
PluginManager *PluginManager::instance()
{
    return m_instance;
}

void PluginManager::addPlugins(const QFileInfoList &plugins)
{
    for (const QFileInfo &fileInfo : plugins) {
        IPluginLoader *pluginLoader = new IPluginLoader(fileInfo.absoluteFilePath());
        instance()->m_p->pluginTree()->addPlugin(pluginLoader);
        instance()->m_p->pluginMap.insert(pluginLoader->name(), pluginLoader);
    }
}

PluginManager::PluginManager():
    m_p(new PluginManagerPrivate(this))
{
    m_instance = this;
    qInstallMessageHandler(PluginManagerPrivate::messageHandler);
    qInfo() << QT_FUNC_NAME <<"Install message handler";
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_p->pluginTree());
    setLayout(layout);
    setVisible(false);
}

void PluginManager::loadPlugins()
{
    /*
     * 按加载顺序加载插件
     */
    for (IPluginLoader *pluginInfo : pluginTreeView()->plugins()) {
        loadPlugin(pluginInfo);
    }
    emit instance()->pluginsLoaded();
}

QWidget *PluginManager::outputWidget()
{
    return instance()->m_p->outputWidget();
}

PluginTreeView *PluginManager::pluginTreeView()
{
    return instance()->m_p->pluginTree();
}

void PluginManager::loadPlugin(IPluginLoader *pluginInfo)
{
    if(pluginInfo->dependencies().isEmpty()) {
        initializePlugin(pluginInfo);
    }
    else
    {
        for(const QVariant &dep : pluginInfo->dependencies())
        {
            loadPlugin(instance()->m_p->pluginMap.value(dep.toString()));
        }
        initializePlugin(pluginInfo);
    }
    pluginInfo->setInitialized(true);
    emit instance()->pluginLoaded(pluginInfo);
}

void PluginManager::initializePlugin(IPluginLoader *pluginLoader)
{
    if (pluginLoader) {
        QObject *plugin = pluginLoader->instance();
        if (plugin && !pluginLoader->initialized()) {
            QString err;
            qobject_cast<IPlugin *>(plugin)->initialize({pluginLoader->fileName()}, &err);
        }
    }
}


PluginManagerPrivate::PluginManagerPrivate(PluginManager *pluginManager)
    :m_outputWidget(new QPlainTextEdit()),
    m_pluginTree(new PluginTreeView())
{
    Q_UNUSED(pluginManager)
}
