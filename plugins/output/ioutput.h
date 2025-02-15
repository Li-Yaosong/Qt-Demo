#ifndef IOUTPUT_H
#define IOUTPUT_H

#include "output_global.h"
#include "iplugin.h"
class OUTPUT_EXPORT IOutput : public IPlugin
{
    Q_OBJECT
    Q_INTERFACES(IPlugin)
    Q_PLUGIN_METADATA(IID IPlugin_iid FILE "output.json")
public:
    explicit IOutput();
private:
    void initialize() final;
};

#endif // IOUTPUT_H
