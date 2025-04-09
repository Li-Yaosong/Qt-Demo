#include "ohremote.h"
#include "ohremotepage.h"

OhRemote::OhRemote() {

}

void OhRemote::initialize()
{
    // qFatal("OhRemote::initialize");
    qputenv("HDC_TOOLCHAIN", "C:\\Users\\liyao\\Documents\\Qt-Demo\\toolchains");
    OhRemotePage::setUpOhRemotePage();
}
