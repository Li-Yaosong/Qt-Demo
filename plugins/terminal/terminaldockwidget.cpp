#include "terminaldockwidget.h"
#include "statusbarmanager.h"
#include "terminaltabwidget.h"
#include "terminalwidget.h"
class TerminalDockWidgetPrivate
{
public:
    TerminalDockWidgetPrivate(TerminalDockWidget *q)
        :terminalTabWidget(new TerminalTabWidget),
        q_ptr(q)
    {
        if(q_ptr)
            q_ptr->setWidget(terminalTabWidget);
        TerminalWidget *terminalWidget = new TerminalWidget(LocalShell, q_ptr);
        terminalWidget->setTerminalFont(QFont("Consolas", 10, QFont::Bold));
        terminalWidget->setBackgroundColor(Qt::black);
        terminalWidget->setForegroundColor(Qt::red);
        // terminalWidget->setMargin(5);
        terminalWidget->setUrlFilterEnabled(0);
        terminalWidget->start({},"",TerminalWidget::PowerShell);
        terminalTabWidget->addTab(terminalWidget, "PowerShell");
        // terminalTabWidget->addTab(new QWidget, "Terminal");
    }
    TerminalTabWidget *terminalTabWidget = nullptr;
private:
    TerminalDockWidget *q_ptr = nullptr;
};

TerminalDockWidget::TerminalDockWidget(const QString &title, QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(title, parent, flags),
      m_p(new TerminalDockWidgetPrivate(this))
{
    setFeatures(QDockWidget::NoDockWidgetFeatures);
}

void TerminalDockWidget::setUpTerminal()
{
    // Q_INIT_RESOURCE(qtermwidget);
    TerminalDockWidget *terminalDockWidget = new TerminalDockWidget("Terminal");
    // IWindow::instance()->addDockWidget(Qt::BottomDockWidgetArea, terminalDockWidget);
    terminalDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
    StatusBarMgr->bindDockWidget(terminalDockWidget, 1);
}
