#include "statusbarmanager.h"
#include "iwindow.h"
#include "statusbar.h"
InstancePtr(StatusBarManager)

class StatusBarManagerPrivate
{
public:
    StatusBarManagerPrivate(StatusBarManager *q)
        : statusBar(new StatusBar),
        q_ptr(q)
    {
        Q_UNUSED(q_ptr)
    }
    StatusBar *statusBar = nullptr;
private:
    StatusBarManager *q_ptr;
};

StatusBarManager::StatusBarManager()
    : QObject{},
    m_p{new StatusBarManagerPrivate(this)}
{

}

StatusBarManager::~StatusBarManager()
{

}

void StatusBarManager::setUpStatusBar()
{
    qDebug() << "SetUpStatusBar";
    IWindow::addStatusBar(StatusBarMgr->m_p->statusBar);
}

void StatusBarManager::bindDockWidget(QDockWidget *dockWidget, int index)
{
    StatusBarMgr->m_p->statusBar->bindDockWidget(dockWidget, index);
}
