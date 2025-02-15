#include "ioutput.h"
#include "outputmanager.h"


IOutput::IOutput() {}

void IOutput::initialize()
{
    OutputManager::setUpOutput();

}
