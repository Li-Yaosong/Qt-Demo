#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H
#include "iwidget.h"
class WelcomePage : public IWidget
{
public:
    WelcomePage(IWidget *parent = nullptr);
    QIcon icon() const;
    int index() const;
    static void setUpWelcomePage();
};
#endif // WELCOMEPAGE_H
