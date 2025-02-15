#include "imenu.h"
InstancePtr(IMenuFactory)
IMenu::IMenu(QWidget *parent)
: QMenu{parent}
{

}

class IMenuFactoryPrivate
{
public:
    IMenuFactoryPrivate(IMenuFactory *q)
        : q_ptr(q)
    {
        Q_UNUSED(q_ptr)
    }
    QMap<QString,IMenu *> m_menus;
private:
    IMenuFactory *q_ptr = nullptr;
};

IMenuFactory::IMenuFactory()
    :m_p(new IMenuFactoryPrivate(this))
{

}
IMenuFactory::~IMenuFactory()
{

}
void IMenuFactory::registerMenu(IMenu *menu)
{
    IMenuFactory::instance()->m_p->m_menus.insert(menu->type(), menu);
    emit IMenuFactory::instance()->menuRegistered(menu);
}

QMap<QString, IMenu *> IMenuFactory::menus()
{
    return m_p->m_menus;
}






