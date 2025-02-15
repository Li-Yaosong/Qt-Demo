#ifndef ITOOLBAR_H
#define ITOOLBAR_H

#include <QGenericPlugin>

class IToolBar
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QGenericPluginFactoryInterface_iid FILE "itoolbar.json")

public:
    explicit IToolBar(QObject *parent = nullptr);

private:
    QObject *create(const QString &name, const QString &spec) override;
};

#endif // ITOOLBAR_H
