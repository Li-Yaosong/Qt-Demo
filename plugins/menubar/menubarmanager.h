#ifndef MENUBARMANAGER_H
#define MENUBARMANAGER_H
#include "menubar_global.h"
#include <QObject>
#include <QMenuBar>
#include "defstruct.h"
#include "imenu.h"
class MenuBar;
class MenuBarManagerPrivate;
class MENUBAR_EXPORT MenuBarManager : public QObject
{
    Q_OBJECT
    Instance(MenuBarManager)
public:

    static void addMenu(IMenu *menu);
    static void setUpMenuBar();
    static void setVisible(bool visible);
    static bool isVisible();
    template <typename T>
    static T *menu()
    {
        return dynamic_cast<T *>(IMenuFactory::instance()->menus().value(T::staticMetaObject.className()));
    }
private:
    MenuBarManagerPrivate * const m_p;
};
#define MenuBarMgr  MenuBarManager::instance()
#endif // MENUBARMANAGER_H
