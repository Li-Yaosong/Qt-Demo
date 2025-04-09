#ifndef STATUSBARMANAGER_H
#define STATUSBARMANAGER_H
#include "statusbar_global.h"
#include <QObject>
#include "defstruct.h"
class StatusBar;
class QDockWidget;
class StatusBarManagerPrivate;
class STATUSBAR_EXPORT StatusBarManager : public QObject
{
    Q_OBJECT
    Instance(StatusBarManager)
public:
    static void setUpStatusBar();
    static void bindDockWidget(QDockWidget *dockWidget, int index = -1);
private:
    StatusBarManagerPrivate * const m_p;
};

#define StatusBarMgr  StatusBarManager::instance()
#endif // STATUSBARMANAGER_H
