#include "statusbar.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "iwindow.h"
#include <QLayout>
#include <QPair>
#include <QDockWidget>
class StatusBarPrivate : public QObject
{
public:
    StatusBarPrivate(StatusBar *q)
        : lable(new QLabel),
          widget(new QWidget),
          q_ptr(q)
    {
        q_ptr->insertPermanentWidget(0, lable);
    }
    bool firstPaint = true;
    QVector<QPushButton *> m_buttons;
    QVector<QDockWidget *> m_dockWidgets;
Q_SLOTS
    void updateLayout(QSize size = QSize())
    {
        Q_UNUSED(size)
        lable->setMinimumWidth(q_ptr->width() - size.width()-5);
        q_ptr->update();
        for(QPushButton * button: std::as_const(m_buttons)) {
            q_ptr->removeWidget(button);
            q_ptr->addPermanentWidget(button);
            button->show();
        }
        q_ptr->addPermanentWidget(widget ,1);
    }
    void changeDockWidget()
    {
        QPushButton *button = qobject_cast<QPushButton *>(QObject::sender());
        if (!button) {
            return;
        }
        QDockWidget *dockWidget = m_dockWidgets.at(m_buttons.indexOf(button));
        if (!dockWidget) {
            return;
        }
        if (m_currentDockWidget && dockWidget == m_currentDockWidget) {
            m_currentDockWidget->setVisible(!m_currentDockWidget->isVisible());
            return;
        }
        m_currentDockWidget = dockWidget;
        m_currentDockWidget->setVisible(true);
    }
private:
    QLabel *lable = nullptr;
    QWidget *widget = nullptr;
    QDockWidget *m_currentDockWidget = nullptr;
    StatusBar *q_ptr = nullptr;
};

StatusBar::StatusBar()
    : QStatusBar()
    , m_p(new StatusBarPrivate(this))
{
    setSizeGripEnabled(false);
    connect(IWindow::instance(), &IWindow::resizeCentralWidget, m_p, &StatusBarPrivate::updateLayout);

}

void StatusBar::bindDockWidget(QDockWidget *dockWidget, int index)
{
    QPushButton *button = new QPushButton(dockWidget->windowTitle());
    button->setFlat(true);
    connect(button, &QPushButton::clicked, m_p, &StatusBarPrivate::changeDockWidget);

    m_p->m_buttons.insert(index, button);
    m_p->m_dockWidgets.insert(index, dockWidget);

    insertPermanentWidget(index, button);
    dockWidget->setVisible(false);
}

void StatusBar::setDefaultShowDockWidget(int index)
{
    if (index >= 0 && index < m_p->m_buttons.size()) {
        m_p->m_buttons.at(index)->click();
    }
}

void StatusBar::paintEvent(QPaintEvent *event)
{
    if (m_p->firstPaint) {
        m_p->firstPaint = false;

        m_p->updateLayout();
    }

    QStatusBar::paintEvent(event);
}
