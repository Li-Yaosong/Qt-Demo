#include "welcomepage.h"
#include "toolbarmanager.h"
#include <QStyle>
#include <QApplication>
WelcomePage::WelcomePage(IWidget *parent)
    :IWidget{parent}
{
    setWindowTitle("Welcome");
}

QIcon WelcomePage::icon() const {
    return QApplication::style()->standardIcon((QStyle::SP_TitleBarMenuButton));
}

int WelcomePage::index() const
{
    return 0;
}

void WelcomePage::setUpWelcomePage()
{
    ToolBarManager::registerWidget<WelcomePage>();
}
