#include "itoolbar.h"

IToolBar::IToolBar(QObject *parent)
    : QGenericPlugin(parent)
{}

QObject *IToolBar::create(const QString &name, const QString &spec)
{
    static_assert(false, "You need to implement this function");
}
