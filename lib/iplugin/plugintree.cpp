#include "plugintree.h"
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
IPluginLoader::IPluginLoader(QObject *parent)
    : QPluginLoader(parent)
{

}

IPluginLoader::IPluginLoader(const QString &fileName, QObject *parent)
    : QPluginLoader(fileName, parent)
{
    QJsonObject metaData = this->metaData();
    /*
         * 提取插件元信息
         * metaData: {
         *     "IID": "com.icode.ui.plugin",
         *     "MetaData": {
         *         "name": "FileMenu",
         *         "dependencies": ["MenuManager"],
         *         "version": "1.0.0"
         *     }
         * }
         */
    if (!metaData.contains("MetaData"))
    {
        qWarning() << "Plugin" << this->fileName() << "does not contain valid metadata.";
        return;
    }

    QJsonObject pluginMetaData = metaData["MetaData"].toObject();
    m_name = pluginMetaData.value("name").toString();
    /*
     * 提取依赖列表
     * 依赖列表格式
     * "dependencies": ["MenuManager", "FileMenu"]
     */
    if (pluginMetaData.contains("dependencies"))
    {
        QJsonArray dependencies = pluginMetaData["dependencies"].toArray();
        m_dependencies = dependencies.toVariantList();
    }
}

QString IPluginLoader::name() const
{
    return m_name;
}

QVariantList IPluginLoader::dependencies() const
{
    return m_dependencies;
}

bool IPluginLoader::initialized() const
{
    return m_initialized;
}

void IPluginLoader::setInitialized(bool initialized)
{
    if (m_initialized == initialized)
        return;

    m_initialized = initialized;
    emit initializedChanged();
}


PluginTreeView::PluginTreeView(QWidget *parent)
    : QTreeView(parent),
    m_model(new PluginTreeModel(this))
{
    setModel(m_model);
    setAlternatingRowColors(true);
}

void PluginTreeView::addPlugin(IPluginLoader *plugin)
{
    m_model->addPlugin(plugin);
}

QVector<IPluginLoader *> PluginTreeView::plugins() const
{
    return m_model->m_plugins;
}

PluginTreeModel::PluginTreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{

}

PluginTreeModel::~PluginTreeModel()
{

}

void PluginTreeModel::addPlugin(IPluginLoader *plugin)
{
    m_plugins << plugin;
}

int PluginTreeModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return m_plugins.size();
    return 0;
}

int PluginTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 4;
}

QVariant PluginTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const IPluginLoader &item = *static_cast<IPluginLoader *>(index.internalPointer());
    // 将 QJsonArray 包装到 QJsonDocument，然后转为 JSON 格式的字符串
    QJsonDocument doc(QJsonArray::fromVariantList(item.dependencies()));
    // ;
    // return QString(doc.toJson(QJsonDocument::Compact));
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0: return item.name();          // 显示插件名称
        case 1: return item.initialized();     // 是否已初始化
        case 2: return QJsonDocument::fromVariant(item.dependencies()).toJson(QJsonDocument::Compact); // 显示依赖项列表（逗号分隔）
        // case 3: return item.fileName(); // 显示插件路径
        default: return QVariant();
        }
    }

    return QVariant();
}

QVariant PluginTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "Plugin Name";
        case 1: return "Initialized";
        case 2: return "Dependencies";
        // case 3: return "File Path";
        default: return QVariant();
        }
    }
    return QVariant();
}

QModelIndex PluginTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid()) {
        return createIndex(row, column, m_plugins[row]);
    }

    return QModelIndex();
}

QModelIndex PluginTreeModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QModelIndex();
}


