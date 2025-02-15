#include "imenubar.h"
#include "menubarmanager.h"
#include "filemenu.h"
#include "viewmenu.h"
#include "helpmenu.h"
IMenuBar::IMenuBar() {}

void IMenuBar::initialize()
{
    MenuBarManager::setUpMenuBar();
    IMenu::setUpMenu<FileMenu>();
    IMenu::setUpMenu<ViewMenu>();
    IMenu::setUpMenu<HelpMenu>();
}
