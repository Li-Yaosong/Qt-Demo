#include "widget.h"
#include "hdc.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("HDC_TOOLCHAIN", "C:\\Users\\liyao\\Documents\\Qt-Demo\\toolchains");
    QApplication a(argc, argv);
    Widget w;

    w.resize(800, 600);
    w.show();
    w.startScreenCasting();
    // w.stopScreenCasting();
    Hdc hdc("C:\\Users\\liyao\\Documents\\Qt-Demo\\toolchains");
    qDebug() << hdc.version();
    // for(auto &str: hdc.help())
    // {
        // qDebug() << str;
    // }
    for (auto &str: hdc.listTargets())
    {
        qDebug() << str;
    }
    hdc.snapshotDisplay();
    return a.exec();
}
