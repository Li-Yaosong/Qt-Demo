#ifndef WELCOME_H
#define WELCOME_H

#include "welcome_global.h"
#include "iplugin.h"
class WELCOME_EXPORT Welcome : public IPlugin
{
    Q_OBJECT
    Q_INTERFACES(IPlugin)
    Q_PLUGIN_METADATA(IID IPlugin_iid FILE "welcome.json")
public:
    explicit Welcome();
private:
    void initialize() final;
};

#endif // WELCOME_H
