#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H
#include "iplugin_global.h"
#include "defstruct.h"
#include <QFileInfo>
class IPluginLoader;
class OutputWidget;
class PluginTreeModel;
class QPlainTextEdit;
class PluginManagerPrivate;
class IPLUGIN_EXPORT PluginManager : public QObject
{
    Q_OBJECT
    friend class PluginManagerPrivate;
    Instance(PluginManager)
public:
    /**
     * @brief addPlugins 添加插件
     * @param plugins 插件列表
     */
    static void addPlugins(const QFileInfoList &plugins);
    /**
     * @brief loadPlugins 加载插件
     */
    static void loadPlugins();
    QStringList previousMessages();
    const PluginTreeModel *pluginTreeModel();
Q_SIGNALS:
    void pluginLoaded(const IPluginLoader *plugin);
    void pluginsLoaded();
    void outputMessage(const QString &message);
private:
    PluginManagerPrivate *m_p = nullptr;
};

#endif // PLUGINMANAGER_H
