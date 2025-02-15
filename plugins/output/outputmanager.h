#ifndef OUTPUTMANAGER_H
#define OUTPUTMANAGER_H

#include <QObject>
#include "defstruct.h"
#include <QDockWidget>
#include <QTextBrowser>

class OutputManagerPrivate;
class OutputManager : public QObject
{
    Q_OBJECT
    Instance(OutputManager)
public:
    static void setOutputVisible(bool visible);
    static bool outputVisible();
    static void setUpOutput();
private:
    OutputManagerPrivate * const m_p;
};
#define OutputMgr  OutputManager::instance()
#endif // OUTPUTMANAGER_H
