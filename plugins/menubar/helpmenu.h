#ifndef HELPMENU_H
#define HELPMENU_H
#include "menubar_global.h"
#include <imenu.h>

class MENUBAR_EXPORT HelpMenu : public IMenu
{
    Q_OBJECT
public:
    explicit HelpMenu(QWidget *parent = nullptr);
    virtual QString  type() final;
private Q_SLOTS:
    void onAbout();
};

#endif // HELPMENU_H
