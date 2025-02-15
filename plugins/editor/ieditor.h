#ifndef IEDITOR_H
#define IEDITOR_H

#include "editor_global.h"
#include "iplugin.h"
class EDITOR_EXPORT IEditor : public IPlugin
{
    Q_OBJECT
    Q_INTERFACES(IPlugin)
    Q_PLUGIN_METADATA(IID IPlugin_iid FILE "editor.json")
public:
    IEditor();
private:
    void initialize() final;
};

#endif // IEDITOR_H
