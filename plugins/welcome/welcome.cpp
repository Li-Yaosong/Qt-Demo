#include "welcome.h"
#include "welcomepage.h"
#include <QDebug>
Welcome::Welcome() {}

void Welcome::initialize()
{
    WelcomePage::setUpWelcomePage();
}
