#ifndef OHREMOTEPAGE_H
#define OHREMOTEPAGE_H

#include <iwidget.h>
class OhRemotePagePrivate;
class OhRemotePage : public IWidget
{
public:
    OhRemotePage(IWidget *parent = nullptr);
    QIcon icon() const;
    int index() const;
    static void setUpOhRemotePage();
private:
    OhRemotePagePrivate * const m_p;
};

#endif // OHREMOTEPAGE_H
