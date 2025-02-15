#include "ohremotepage.h"
#include "toolbarmanager.h"
#include <QStyle>
#include <QApplication>
OhRemotePage::OhRemotePage(IWidget *parent)
    :IWidget{parent}
{
    setWindowTitle("Remote");
}

QIcon OhRemotePage::icon() const
{
    return QApplication::style()->standardIcon((QStyle::SP_TitleBarMenuButton));
}

int OhRemotePage::index() const
{
    return 2;
}

void OhRemotePage::setUpOhRemotePage()
{
    ToolBarManager::registerWidget<OhRemotePage>();
}
