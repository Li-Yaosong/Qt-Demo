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
    ~OutputWidget();
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
        StatusBarMgr->bindDockWidget(m_outputWidget, 0);
    }
    ~OutputManagerPrivate()
    {
        if (m_outputWidget)
            m_outputWidget->deleteLater();
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
    if (m_p)
        delete m_p;
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
    OutputManager::instance();
    // IWindow::instance()->addDockWidget(Qt::BottomDockWidgetArea, OutputManager::instance()->m_p->outputWidget());
}
class OutputWidgetPrivate
{
public:
    OutputWidgetPrivate(OutputWidget *q)
        : q_ptr(q)
    {
        Q_UNUSED(q_ptr)

    }
    ~OutputWidgetPrivate()
    {
    }
private:
    OutputWidget *q_ptr = nullptr;
};

OutputWidget::OutputWidget(const QString &title, QWidget *parent, Qt::WindowFlags flags)
    : QDockWidget(title, parent, flags),
      m_p(new OutputWidgetPrivate(this))
{
    QPlainTextEdit *outputWidget = new QPlainTextEdit(this);
    outputWidget->setReadOnly(true);
    outputWidget->setLineWrapMode(QPlainTextEdit::NoWrap);

    QStringList previousMessages = PluginManager::instance()->previousMessages();
    for(const QString &message : std::as_const(previousMessages))
        outputWidget->appendPlainText(message);

    connect(PluginManager::instance(), &PluginManager::outputMessage, outputWidget, &QPlainTextEdit::appendHtml);
    setWidget(outputWidget);
    ViewMenu *viewMenu = MenuBarManager::menu<ViewMenu>();
    QAction *showOutput = viewMenu->addAction(tr("Show Output"));
    showOutput->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_O));
    addAction(showOutput);
    IWindow::instance()->addAction(showOutput);
    connect(showOutput, &QAction::triggered, this, &OutputWidget::outputWidgetShowOrHide);
}

OutputWidget::~OutputWidget()
{
    if (m_p)
        delete m_p;
}


