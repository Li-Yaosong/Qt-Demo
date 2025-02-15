#ifndef OHREMOTEPAGE_H
#define OHREMOTEPAGE_H

#include <iwidget.h>

class OhRemotePage : public IWidget
{
public:
    OhRemotePage(IWidget *parent = nullptr);
    QIcon icon() const;
    int index() const;
    static void setUpOhRemotePage();
};

#endif // OHREMOTEPAGE_H
