#include "terminalwidget.h"
#include "ptyqt.h"
#include "qdir.h"
#include <QFileInfo>
#include <QProcessEnvironment>
#include <QApplication>
class TerminalWidgetPrivate
{
public:
    explicit TerminalWidgetPrivate(TerminalWidget *q)
        : q_ptr(q)
    {
        Q_UNUSED(q_ptr);
    }
    IPtyProcess *localShell = nullptr;
private:
    TerminalWidget *q_ptr = nullptr;
};

TerminalWidget::TerminalWidget(TerminalType type, QWidget *parent)
    : QTermWidget(parent)
    , m_p(new TerminalWidgetPrivate(this))
{
    setScrollBarPosition(QTermWidget::ScrollBarRight);
    setBlinkingCursor(true);
    setMargin(5, 3);
    setDrawLineChars(false);
    setSelectionOpacity(0.5);
    setShowResizeNotificationEnabled(false);
    QStringList availableColorSchemes = this->availableColorSchemes();
    // availableColorSchemes.sort();
    qDebug() << availableColorSchemes.count();
    switch (type) {

    case LocalShell:
    {
        m_p->localShell = PtyQt::createPtyProcess(IPtyProcess::PtyType::ConPty);
        connect(this, &QTermWidget::termSizeChange, this, [=](int lines, int columns){
            m_p->localShell->resize(columns,lines);
        });
        break;
    }
    default:
        break;
    }
    connect(m_p->localShell->notifier(), &QIODevice::readyRead, this, [=](){
        QByteArray data = m_p->localShell->readAll();
        recvData(data.data(), data.size());
    });
    connect(m_p->localShell->notifier(), &QIODevice::readyRead, this, &TerminalWidget::clearScrollback,
            Qt::SingleShotConnection);
    connect(this, &QTermWidget::sendData, this, [=](const char *data, int size){
        m_p->localShell->write(QByteArray(data, size));
    });

}

TerminalWidget::~TerminalWidget()
{

}

int TerminalWidget::start(const QString &command, QString profile, ShellType sTp)
{
    Q_UNUSED(command);
    QString shellPath;
    QStringList args;
#if defined(Q_OS_WIN)
    // QString wslUserName = "root";
    // QString wslDistro = "Ubuntu";

    switch (sTp) {
#if defined(Q_OS_UNIX)
    case UnixShell:
        break;
#endif
    case PowerShell:
    {
        QString defaultLocalShell = "c:\\Windows\\system32\\WindowsPowerShell\\v1.0\\powershell.exe";
        QFileInfo shellInfo(defaultLocalShell);
        if(shellInfo.isExecutable()) {
            shellPath = defaultLocalShell;
        }
        if(shellPath.isEmpty()) shellPath = "c:\\Windows\\system32\\WindowsPowerShell\\v1.0\\powershell.exe";
        args = QStringList{
            "-ExecutionPolicy",
            "Bypass",
            "-NoLogo",
            "-NoProfile",
            "-NoExit",
            "-File"
        };
        if(profile.isEmpty()) {
            profile = QString("\"") + "c:/Windows/System32/WindowsPowerShell/v1.0/Examples/Profile.ps1\"";
        } else {
            profile = QString("\"") + profile + "\"";
        }
        args.append(profile);
        break;
    }
    case WSL:
    {
        shellPath = "C:\\Windows\\System32\\wsl.exe";
        // args = QStringList{
        //     "-e",
        //     "bash",
        //     "-c",
        //     "\"clear; exec bash\"",
        // };
        break;
    }
    case Unknown:
        break;
    }
#endif
    QStringList envs = QProcessEnvironment::systemEnvironment().toStringList();
    // qDebug() << "envs: " << envs;

    bool ret = m_p->localShell->startProcess(shellPath, args, QDir::homePath(), envs, screenColumnsCount(), screenLinesCount());
    if(!ret) {
        return -1;
    }
    return 0;
}

void TerminalWidget::resizeEvent(QResizeEvent *event)
{
    QTermWidget::resizeEvent(event);
    m_p->localShell->resize(screenColumnsCount(), screenLinesCount());
    update();
}
