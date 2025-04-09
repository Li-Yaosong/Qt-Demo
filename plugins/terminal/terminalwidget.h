#ifndef TERMINALWIDGET_H
#define TERMINALWIDGET_H
#include "qtermwidget.h"
class TerminalWidgetPrivate;
enum TerminalType {
    LocalShell,
};
class TerminalWidget : public QTermWidget
{
public:
    enum ShellType {
    #if defined(Q_OS_UNIX)
        UnixShell = 0,
    #endif
        PowerShell,
        WSL,
        Unknown,
    };
    explicit TerminalWidget(TerminalType type, QWidget *parent = nullptr);
    ~TerminalWidget();
#if defined(Q_OS_WIN)
    int start(const QString &command, QString profile = QString(), ShellType sTp = PowerShell);
#endif
protected:
    void resizeEvent(QResizeEvent *event);
private:
    std::unique_ptr<TerminalWidgetPrivate> m_p = nullptr;

    // QWidget interface

};

#endif // TERMINALWIDGET_H
