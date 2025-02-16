#include "outputmanager.h"
#include "iwindow.h"
#include "pluginmanager.h"
#include <QMutex>
#include <QApplication>
#include <QPlainTextEdit>
#include "viewmenu.h"
#include "menubarmanager.h"
#include "statusbarmanager.h"
InstancePtr(OutputManager)
class OutputWidgetPrivate;
class OutputWidget : public QDockWidget
{
public:
    explicit OutputWidget(const QString &title, QWidget *parent = nullptr,
                          Qt::WindowFlags flags = Qt::WindowFlags());
    void outputWidgetShowOrHide()
    {
        OutputManager::setOutputVisible(!OutputManager::outputVisible());
    }
private:
    OutputWidgetPrivate * const m_p;
};

class OutputManagerPrivate
{
public:
    OutputManagerPrivate(OutputManager *q)
        : m_outputWidget(new OutputWidget("Output")),
        q_ptr(q)
    {
        Q_UNUSED(q_ptr)
        m_outputWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        StatusBarMgr->bindDockWidget(m_outputWidget);
    }
    OutputWidget *outputWidget()
    {
        return m_outputWidget;
    }

private:
    OutputWidget *m_outputWidget = nullptr;
    OutputManager *q_ptr = nullptr;
};

OutputManager::OutputManager()
    : m_p(new OutputManagerPrivate(this))
{
    qDebug() << "OutputManager";
}

OutputManager::~OutputManager()
{

}

void OutputManager::setOutputVisible(bool visible)
{
    OutputManager::instance()->m_p->outputWidget()->setVisible(visible);
}

bool OutputManager::outputVisible()
{
    return OutputManager::instance()->m_p->outputWidget()->isVisible();
}

void OutputManager::setUpOutput()
{

    IWindow::instance()->addDockWidget(Qt::BottomDockWidgetArea, OutputManager::instance()->m_p->outputWidget());
}
class OutputWidgetPrivate
{
public:
    OutputWidgetPrivate(OutputWidget *q)
        : q_ptr(q)
    {
        Q_UNUSED(q_ptr)

    }
    void setOutputWidget(QWidget *widget)
    {
        m_outputWidget = dynamic_cast<QPlainTextEdit *>(widget);
        if (m_outputWidget) {
            m_outputWidget->setReadOnly(true);
        }

    }
    QPlainTextEdit *outputWidget()
    {
        return m_outputWidget;
    }
    QPlainTextEdit *m_outputWidget = nullptr;
private:
    OutputWidget *q_ptr = nullptr;
};

OutputWidget::OutputWidget(const QString &title, QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(title, parent, flags),
      m_p(new OutputWidgetPrivate(this))
{
    m_p->setOutputWidget(PluginManager::instance()->outputWidget());
    setWidget(m_p->outputWidget());
    ViewMenu *viewMenu = MenuBarManager::menu<ViewMenu>();
    QAction *showOutput = viewMenu->addAction(tr("Show Output"));
    showOutput->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_O));
    addAction(showOutput);
    IWindow::instance()->addAction(showOutput);
    connect(showOutput, &QAction::triggered, this, &OutputWidget::outputWidgetShowOrHide);
}


