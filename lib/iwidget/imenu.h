#ifndef IMENU_H
#define IMENU_H
#include "iwidget_global.h"
#include <QMenu>
#include <defstruct.h>
class IMenu;
class IMenuFactoryPrivate;
class IWIDGET_EXPORT IMenuFactory : public QObject
{
    Q_OBJECT
    Instance(IMenuFactory)
    friend class MenuBarManager;
    friend class IMenu;
public:
    static void registerMenu(IMenu *menu);
Q_SIGNALS:
    void menuRegistered(IMenu *menu);
private:
    QMap<QString, IMenu *> menus();
    IMenuFactoryPrivate * const m_p;
};

class IWIDGET_EXPORT IMenu  : public QMenu
{
    Q_OBJECT
public:
    explicit IMenu(QWidget *parent = nullptr);
    template <typename T>
    IMenu(T *menu)
    {
        IMenuFactory::registerMenu(menu);
    }
    virtual QString  type() = 0;

    template <typename T>
    inline static QString  type()
    {
        // T *menu = IMenuFactory::menu<T>();
        IMenu *menu = IMenuFactory::instance()->menus().value(T::staticMetaObject.className());
        if(menu)
        {
            return T::staticMetaObject.className();
        }
        else
        {
            qDebug() << QString("Menu type: '%1' not registered").arg(T::staticMetaObject.className());
            return QString();
        }

    }
    template <typename T>
    inline static void setUpMenu()
    {
        new T();
        qDebug() << QString("Menu type: '%1' setup").arg(T::staticMetaObject.className());
    }
};

#endif // IMENU_H
