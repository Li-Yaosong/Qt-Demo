#ifndef ISTATUSBAR_H
#define ISTATUSBAR_H

#include "statusbar_global.h"
#include "iplugin.h"
class STATUSBAR_EXPORT IStatusBar : public IPlugin
{
    Q_OBJECT
    Q_INTERFACES(IPlugin)
    Q_PLUGIN_METADATA(IID IPlugin_iid FILE "statusbar.json")
public:
    IStatusBar();
private:
    void initialize() final;
};

#endif // ISTATUSBAR_H
