#include "viewmenu.h"
#include "menubarmanager.h"
#include <QShortcut>
#include <iwindow.h>
ViewMenu::ViewMenu(QWidget *parent)
    :IMenu(parent)
{
    IMenuFactory::registerMenu(this);
    setTitle(tr("&View"));
    QAction *hideMenuBar = new QAction(tr("&Hide Menu Bar"), this);
    hideMenuBar->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_T));
    addAction(hideMenuBar);
    IWindow::instance()->addAction(hideMenuBar);
    connect(hideMenuBar, &QAction::triggered, this, &ViewMenu::menuBarShowOrHide);
}

QString ViewMenu::type()
{
    return metaObject()->className();
}

void ViewMenu::menuBarShowOrHide()
{
    qDebug() << "ViewMenu::menuBarShowOrHide()";
    MenuBarManager::setVisible(!MenuBarManager::isVisible());
}
