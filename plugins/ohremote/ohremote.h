#ifndef OHREMOTE_H
#define OHREMOTE_H

#include "ohremote_global.h"
#include "iplugin.h"
class OHREMOTE_EXPORT OhRemote : public IPlugin
{
    Q_OBJECT
    Q_INTERFACES(IPlugin)
    Q_PLUGIN_METADATA(IID IPlugin_iid FILE "ohremote.json")
public:
    explicit OhRemote();
private:
    void initialize() final;
};

#endif // OHREMOTE_H
