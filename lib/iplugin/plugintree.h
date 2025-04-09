#ifndef PLUGINTREE_H
#define PLUGINTREE_H

#include <QAbstractItemModel>
#include <QVariant>
#include <QPluginLoader>

class IPluginLoader : public QPluginLoader
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QVariantList dependencies READ dependencies CONSTANT)
    Q_PROPERTY(bool initialized READ initialized WRITE setInitialized NOTIFY initializedChanged)

public:
    explicit IPluginLoader(QObject *parent = nullptr);
    explicit IPluginLoader(const QString &fileName, QObject *parent = nullptr);
    ~IPluginLoader();

    QString name() const;

    QVariantList dependencies() const;

    bool initialized() const;
    void setInitialized(bool initialized);

Q_SIGNALS:
    void initializedChanged();

private:
    QString m_name;
    QVariantList m_dependencies;
    bool m_initialized = false;
};

class PluginTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    friend class PluginManager;
    explicit PluginTreeModel(QObject *parent = nullptr);
    ~PluginTreeModel();

    void addPlugin(IPluginLoader *plugin);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

private:
    QVector<IPluginLoader *> m_plugins;
};

#endif // PLUGINTREE_H
