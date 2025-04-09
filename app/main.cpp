#include <iapplication.h>

int main(int argc, char *argv[])
{  
    IApplication app(argc, argv);

    IApplication::qtDebugPlugins(true);

    return app.exec();
}
