#ifndef OHSCREENMIRROR_H
#define OHSCREENMIRROR_H

#include "hdc_global.h"
#include <QObject>
class OhScreenMirrorPrivate;
class HDC_EXPORT OhScreenMirror : public QObject
{
    Q_OBJECT
public:
    explicit OhScreenMirror(QObject *parent = nullptr);

    ~OhScreenMirror();

    void start();
    void stop();

signals:
    void screenFlush(const QImage &);

private:
    friend class ScreenMirrorHeper;
    OhScreenMirrorPrivate *m_p = nullptr;
};

#endif // OHSCREENMIRROR_H
