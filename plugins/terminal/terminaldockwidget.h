#ifndef TERMINALDOCKWIDGET_H
#define TERMINALDOCKWIDGET_H

#include <QDockWidget>
class TerminalDockWidgetPrivate;
class TerminalDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit TerminalDockWidget(const QString &title, QWidget *parent = nullptr,
                       Qt::WindowFlags flags = Qt::WindowFlags());
    void terminalWidgetShowOrHide();
    static void setUpTerminal();
private:
    TerminalDockWidgetPrivate * const m_p;
};

#endif // TERMINALDOCKWIDGET_H
