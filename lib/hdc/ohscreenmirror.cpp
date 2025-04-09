#include "ohscreenmirror.h"
#include "hdc.h"
#include <QImage>
#include <QtConcurrentRun>
#include <QDebug>
class OhScreenMirrorPrivate
{
public:
    OhScreenMirrorPrivate()
        :hdc{new Hdc}
    {
        QString hdcPath = qgetenv("HDC_TOOLCHAIN");
        if (!hdcPath.isEmpty())
        {
            qDebug() << "HDC_TOOLCHAIN" << hdcPath;
            hdc->setPath(hdcPath);
        }
    }
    ~OhScreenMirrorPrivate()
    {
        qDebug() << "OhScreenMirrorPrivate delete";
        startScreenMirror = false;

        if (hdc)
        {
            hdc->quit();
            delete hdc;
            hdc = nullptr;
        }
    }
    friend class OhScreenMirror;
    friend class ScreenMirrorHeper;

private:
    QList<ScreenMirrorHeper *> helpers;
    bool startScreenMirror = false;
    Hdc *hdc = nullptr;
};

class ScreenMirrorHeper : public QObject
{
public:
    ScreenMirrorHeper(OhScreenMirror * m, QObject *parent = nullptr)
        : QObject(parent),
        mirror(m)
    {
        auto future = QtConcurrent::run(&ScreenMirrorHeper::start, this);
    }
    ~ScreenMirrorHeper()
    {
        qDebug() << "ScreenMirrorHeper delete";
    }
    void start()
    {
        qDebug() << "start" << QThread::currentThreadId();
        while (mirror->m_p->startScreenMirror)
        {
            if(mirror)
                emit mirror->screenFlush(mirror->m_p->hdc->snapshotDisplay());
        }
        mirror->m_p->helpers.removeAll(this);
        deleteLater();
    }
private:
    OhScreenMirror *mirror = nullptr;
};

OhScreenMirror::OhScreenMirror(QObject *parent)
    : QObject{parent},
    m_p{new OhScreenMirrorPrivate}
{}

OhScreenMirror::~OhScreenMirror()
{
    qDebug() << "OhScreenMirror delete";
    if (m_p->startScreenMirror)
    {
        stop();
    }
    if (m_p)
    {
        delete m_p;
        m_p = nullptr;
    }
}

void OhScreenMirror::start()
{
    m_p->startScreenMirror = true;
    int threadCount = 8;
    qDebug() << "Start screen casting threadCount" << threadCount;

    for(int i = 0; i < threadCount; i++)
    {
        m_p->helpers.append(new ScreenMirrorHeper(this));
    }
}

void OhScreenMirror::stop()
{
    m_p->startScreenMirror = false;
    int threadCount = -1;
    while(!m_p->helpers.isEmpty())
    {
        if(m_p->helpers.count() != threadCount)
        {
            threadCount = m_p->helpers.count();
            if(threadCount == 0)
            {
                break;
            }
            qDebug() << "Wait for the remaining" << threadCount << "threads to exit";
        }
    }
}
