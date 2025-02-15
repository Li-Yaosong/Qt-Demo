#ifndef VIEWMENU_H
#define VIEWMENU_H
#include "menubar_global.h"
#include <imenu.h>

class MENUBAR_EXPORT ViewMenu : public IMenu
{
    Q_OBJECT
public:
    explicit ViewMenu(QWidget *parent = nullptr);
    virtual QString  type() final;
private Q_SLOTS:
    void menuBarShowOrHide();
};

#endif // VIEWMENU_H
