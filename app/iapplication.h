#ifndef IAPPLICATION_H
#define IAPPLICATION_H
#include <QApplication>

class IApplicationPrivate;
class  IApplication : public QObject
{
    Q_OBJECT
public:
    explicit IApplication(int &argc, char **argv);

    static void qtDebugPlugins(bool enabled);
    int exec();
    ~IApplication();
Q_SIGNALS:
    void appCreated();
private:
    IApplicationPrivate *d_ptr;
};

#endif // IAPPLICATION_H
