#include "itoolbar.h"
#include "toolbarmanager.h"

IToolbar::IToolbar()
{

}

void IToolbar::initialize()
{
    ToolBarManager::setUpToolBar();
}
