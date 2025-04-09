#include "iterminal.h"
#include "terminaldockwidget.h"
ITerminal::ITerminal() {}

void ITerminal::initialize()
{
    TerminalDockWidget::setUpTerminal();
}
