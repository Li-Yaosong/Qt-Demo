#include <qtermwidget.h>
#include <iptyprocess.h>
#include <ptyqt.h>
#include <QApplication>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QProcessEnvironment>
#include <QMessageBox>
#include "sessionswindow.h"
#include "remoteterm.h"
#include "qfonticon.h"
#include <QDockWidget>

int main(int argc, char *argv[])
{
    // Q_INIT_RESOURCE(qtermwidget);
    QApplication a(argc, argv);
    QFontIcon::addFont(":/icons/icons/fontawesome-webfont-v6.6.0-solid-900.ttf");
    QFontIcon::addFont(":/icons/icons/fontawesome-webfont-v6.6.0-brands-400.ttf");
    // QFontIcon::instance()->setColor(isDarkTheme?Qt::white:Qt::black);
    QDockWidget *dockWidget = new QDockWidget("Terminal");
    RemoteTerm w;
    SessionsWindow *sessionsWindow = new SessionsWindow(SessionsWindow::LocalShell);
    sessionsWindow->setTerminalFont(QFont("consolas", 12));
    sessionsWindow->setLongTitle(SessionsWindow::tr("Local Shell"));
    sessionsWindow->setShortTitle(SessionsWindow::tr("Local Shell"));
    sessionsWindow->setName(SessionsWindow::tr("Local Shell"));
    sessionsWindow->setWorkingDirectory(QDir::homePath());
    sessionsWindow->startLocalShellSession({},"");
    w.addTab(sessionsWindow->getMainWidget(), sessionsWindow->getTitle());
    dockWidget->setWidget(&w);
    dockWidget->show();
    return a.exec();
}
// res
