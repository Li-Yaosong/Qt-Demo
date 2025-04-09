#ifndef ITERMINAL_H
#define ITERMINAL_H

#include "terminal_global.h"
#include "iplugin.h"
class TERMINAL_EXPORT ITerminal : public IPlugin
{
    Q_OBJECT
    Q_INTERFACES(IPlugin)
    Q_PLUGIN_METADATA(IID IPlugin_iid FILE "terminal.json")
public:
    explicit ITerminal();
private:
    void initialize() final;
};

#endif // ITERMINAL_H
