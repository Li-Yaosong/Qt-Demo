#ifndef IMENUBAR_H
#define IMENUBAR_H

#include "menubar_global.h"
#include "iplugin.h"
class MENUBAR_EXPORT IMenuBar : public IPlugin
{
    Q_OBJECT
    Q_INTERFACES(IPlugin)
    Q_PLUGIN_METADATA(IID IPlugin_iid FILE "menubar.json")
public:
    IMenuBar();
private:
    void initialize() final;
};

#endif // IMENUBAR_H
