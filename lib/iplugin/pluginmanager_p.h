#ifndef PLUGINMANAGER_P_H
#define PLUGINMANAGER_P_H
#include <QObject>
#include "pluginmanager.h"
// #include "qsciscintilla.h"
#include <QPlainTextEdit>
#include <QMutex>
#include <QDateTime>
#include <QMap>
#include <QQueue>
#include <QDebug>
#include "plugintree.h"
class PluginManager;
class PluginManagerPrivate : public QObject
{
public:
    PluginManagerPrivate(PluginManager *pluginManager);
    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
    {
        Q_UNUSED(context);
        static QMutex mutex;
        QMutexLocker locker(&mutex);

        QString logLevel;
        QString color;
        switch (type)
        {
        case QtDebugMsg:
            logLevel = "DEBUG";
            color = "black";
            break;
        case QtInfoMsg:
            logLevel = "INFO";
            color = "blue";
            break;
        case QtWarningMsg:
            logLevel = "WARNING";
            color = "orange";
            break;
        case QtCriticalMsg:
            logLevel = "CRITICAL";
            color = "red";
            break;
        case QtFatalMsg:
            logLevel = "FATAL";
            color = "darkred";
            break;
        }
        QString coloredLogLevel = QString("<span style='color:darkred;'>%1</span>")
                                      .arg(logLevel);
        QString formattedMessage = QString("[%1] [%2] %3") // (%4:%5, %6)
                                       .arg(QDateTime::currentDateTime().toString("yyyy.MM.dd HH:mm:ss"))
                                       .arg(logLevel)
                                       .arg(msg);
        QString htmlMessage = QString("<span style='color:%1;'>%2</span>").arg(color).arg(formattedMessage);

        // qDebug()<< formattedMessage.toLocal8Bit().constData();
        // qDebug()<< (stderr, "%s\n", );
        fflush(stderr);

        // if (!PluginManager::instance()->m_p->outputWidget().isEmpty()) {
        //     formattedMessage.prepend("\n");
        // }
        PluginManager::instance()->m_p->outputWidget()->appendHtml(htmlMessage);
    }
    QPlainTextEdit *outputWidget()
    {
        return m_outputWidget;
    }
    PluginTreeView *pluginTree()
    {
        return m_pluginTree;
    }
    // QVector<IPluginLoader *> plugins;
    QMap<QString, IPluginLoader *> pluginMap;
    // QFileInfoList plugins;
private:
    QPlainTextEdit *m_outputWidget = nullptr;
    PluginTreeView *m_pluginTree = nullptr;
};

#endif // PLUGINMANAGER_P_H

