#include "istatusbar.h"
#include "statusbarmanager.h"
IStatusBar::IStatusBar() {}

void IStatusBar::initialize()
{
    StatusBarManager::setUpStatusBar();
}
