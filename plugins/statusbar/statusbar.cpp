#include "statusbar.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "iwindow.h"
#include <QLayout>
#include <QPair>
#include <QDockWidget>
#include <QButtonGroup>
#include <QTabBar>
class StatusBarPrivate : public QObject
{
public:
    StatusBarPrivate(StatusBar *q)
        :m_buttonGroup(new QButtonGroup),
        bottomDockWidget(new QDockWidget),
        tabWidget(new QTabWidget),
        lable(new QLabel),
        widget(new QWidget),
        q_ptr(q)
    {
        IWindow::instance()->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, bottomDockWidget);
        bottomDockWidget->setFeatures(QDockWidget::NoDockWidgetFeatures);
        bottomDockWidget->setWidget(tabWidget);
        tabWidget->tabBar()->hide();
        q_ptr->insertPermanentWidget(0, lable);
    }
    bool firstPaint = true;
    QButtonGroup *m_buttonGroup = nullptr;
    QDockWidget *bottomDockWidget = nullptr;
    QTabWidget *tabWidget = nullptr;
Q_SLOTS
    void updateLayout(QSize size = QSize())
    {
        Q_UNUSED(size)
        lable->setMinimumWidth(q_ptr->width() - size.width()-5);
        q_ptr->update();
        int buttonCount = m_buttonGroup->buttons().size();
        for (int var = 0; var < buttonCount; ++var) {
            QAbstractButton *button = m_buttonGroup->button(var);
            q_ptr->removeWidget(button);
            q_ptr->addPermanentWidget(button);
            button->show();
        }
        q_ptr->addPermanentWidget(widget ,1);
    }
    void changeDockWidget(int id)
    {
        tabWidget->setCurrentIndex(id);
        bool visible = currentId == id ? !bottomDockWidget->isVisible() : true;
        bottomDockWidget->setVisible(visible);
        currentId = id;
        bottomDockWidget->setWindowTitle(m_buttonGroup->button(id)->text());
    }
private:
    QLabel *lable = nullptr;
    QWidget *widget = nullptr;
    int currentId = -1;
    StatusBar *q_ptr = nullptr;
};

StatusBar::StatusBar()
    : QStatusBar()
    , m_p(new StatusBarPrivate(this))
{
    setSizeGripEnabled(false);
    connect(IWindow::instance(), &IWindow::resizeCentralWidget, m_p, &StatusBarPrivate::updateLayout);
    connect(m_p->m_buttonGroup, QOverload<int>::of(&QButtonGroup::idClicked), m_p, &StatusBarPrivate::changeDockWidget);
}

void StatusBar::bindDockWidget(QDockWidget *dockWidget, int index)
{
    qDebug () << "bindDockWidget" << index;
    QPushButton *button = new QPushButton(dockWidget->windowTitle());
    button->setFlat(true);
    if (index == -1) {
        index = m_p->m_buttonGroup->buttons().size();
    }
    m_p->m_buttonGroup->addButton(button, index);
    m_p->tabWidget->insertTab(index, dockWidget, dockWidget->windowTitle());

    insertPermanentWidget(index, button);
    setDefaultShowDockWidget(index);
}

void StatusBar::setDefaultShowDockWidget(int index)
{
    m_p->m_buttonGroup->button(index)->click();
}

void StatusBar::paintEvent(QPaintEvent *event)
{
    if (m_p->firstPaint) {
        m_p->firstPaint = false;

        m_p->updateLayout();
    }

    QStatusBar::paintEvent(event);
}
