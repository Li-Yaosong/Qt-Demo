#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H
#include "iplugin_global.h"

#include <QDialog>
#include <QFileInfo>
class IPluginLoader;
class OutputWidget;
class PluginTreeView;

class PluginManagerPrivate;
class IPLUGIN_EXPORT PluginManager : public QDialog
{
    Q_OBJECT
    friend class PluginManagerPrivate;
    friend class OutputWidget;
public:
    static PluginManager *instance();
    /**
     * @brief addPlugins 添加插件
     * @param plugins 插件列表
     */
    static void addPlugins(const QFileInfoList &plugins);
    PluginManager();

    /**
     * @brief loadPlugins 加载插件
     */
    static void loadPlugins();
private:
    /**
     * @brief outputWidget 输出窗口
     * @return
     */
    static QWidget *outputWidget();
    static PluginTreeView *pluginTreeView();
    /**
     * @brief loadPlugin 加载插件
     * @param pluginInfo 插件信息
     */
    static void loadPlugin(IPluginLoader *pluginInfo);
    /**
     * @brief initializePlugin 初始化插件
     * @param pluginLoader 插件信息
     */
    static void initializePlugin(IPluginLoader *pluginLoader);
Q_SIGNALS:
    void pluginLoaded(const IPluginLoader *plugin);
    void pluginsLoaded();
private:
    PluginManagerPrivate *m_p = nullptr;
};

#endif // PLUGINMANAGER_H
