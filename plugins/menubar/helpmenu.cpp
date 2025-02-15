#include "helpmenu.h"
#include <QStyle>
#include <QApplication>
#include <QMessageBox>
#include <iwindow.h>
#include "pluginmanager.h"
HelpMenu::HelpMenu(QWidget *parent)
    : IMenu(parent)
{
    IMenuFactory::registerMenu(this);
    setTitle(tr("&Help"));
    QAction *aboutPluginAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation),
                                             tr("&About Plugin"), this);
    // IWindow::instance()->addAction(aboutPluginAction);
    PluginManager::instance()->setParent(IWindow::instance(), Qt::WindowType::Dialog);
    connect(aboutPluginAction, &QAction::triggered, PluginManager::instance(), &PluginManager::show);
    addAction(aboutPluginAction);
    QAction *aboutAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation),
                                       tr("&About"), this);
    // IWindow::instance()->addAction(aboutAction);
    connect(aboutAction, &QAction::triggered, this, &HelpMenu::onAbout);
    addAction(aboutAction);
}

QString HelpMenu::type()
{
    return metaObject()->className();
}

void HelpMenu::onAbout()
{
    QMessageBox::about(IWindow::instance(), tr("About"), tr("This is a simple text editor"));
}
