#ifndef ITOOLBAR_H
#define ITOOLBAR_H

#include "toolbar_global.h"
#include "iplugin.h"
class TOOLBAR_EXPORT IToolbar : public IPlugin
{
    Q_OBJECT
    Q_INTERFACES(IPlugin)
    Q_PLUGIN_METADATA(IID IPlugin_iid FILE "toolbar.json")
public:
    explicit IToolbar();
private:
    void initialize() final;
};
#endif // ITOOLBAR_H
