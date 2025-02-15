#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
class MenuBarPrivate;
class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    MenuBar();
private:
    MenuBarPrivate * const m_p;
};

#endif // MENUBAR_H
