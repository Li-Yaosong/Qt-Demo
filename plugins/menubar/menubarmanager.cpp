#include "menubarmanager.h"
#include "iwindow.h"
#include "menubar.h"
InstancePtr(MenuBarManager)


class MenuBarManagerPrivate
{
public:
    MenuBarManagerPrivate(MenuBarManager *q)
        : menuBar(new MenuBar),
        q_ptr(q)
    {
        Q_UNUSED(q_ptr)
    }
    MenuBar *menuBar = nullptr;
private:
    MenuBarManager *q_ptr = nullptr;
};

MenuBarManager::MenuBarManager()
    : QObject{}
    , m_p(new MenuBarManagerPrivate(this))
{
    connect(IMenuFactory::instance(), &IMenuFactory::menuRegistered, this, &MenuBarManager::addMenu);
}

MenuBarManager::~MenuBarManager()
{

}

void MenuBarManager::addMenu(IMenu *menu)
{
    MenuBarMgr->m_p->menuBar->addMenu(menu);
}

void MenuBarManager::setUpMenuBar()
{
    qDebug() << "SetUpMenuBar";
    IWindow::addMenuBar(MenuBarMgr->m_p->menuBar);
}

void MenuBarManager::setVisible(bool visible)
{
    MenuBarMgr->m_p->menuBar->setVisible(visible);
}

bool MenuBarManager::isVisible()
{
    return MenuBarMgr->m_p->menuBar->isVisible();
}
