#include "toolbarmanager.h"
#include <QToolBar>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QToolButton>
#include <QTabBar>
#include "iwindow.h"
#include "iwidget.h"
#include "pluginmanager.h"
#include "icentralwidget.h"
#include "qevent.h"
#include "qmenu.h"
#include "menubarmanager.h"
#include "viewmenu.h"
#include <QApplication>
InstancePtr(ToolBarManager)
class ToolBarManagerPrivate
{
public:
    ToolBarManagerPrivate()
        :toolBar(new ToolBar),
        centralWidget(new ICentralWidget)
    {
        toolBar->setCentralWidget(centralWidget);
        IWindow::addCentralWidget(centralWidget);
    }
    ~ToolBarManagerPrivate()
    {
        delete toolBar;
        delete centralWidget;
    }
    ToolBar *toolBar = nullptr;
    ICentralWidget * centralWidget = nullptr;
    QHash<int, QAction *> actions;
};

ToolBarManager::ToolBarManager()
    :m_p(new ToolBarManagerPrivate)
{
    connect(qApp, &QApplication::aboutToQuit, this, &ToolBarManager::destroy);
}
ToolBarManager::~ToolBarManager()
{
    delete m_p;
}
class ToolBarPrivate
{
public:
    ToolBarPrivate(ToolBar *q = nullptr):
        buttonGroup(new QButtonGroup),
        contextMenu(new QMenu(q)),
        layout(new QVBoxLayout),
        q_ptr(q)
    {
        q_ptr->setContextMenuPolicy(Qt::PreventContextMenu); // 禁用右键菜单
        q_ptr->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        q_ptr->setMovable(false);
        q_ptr->setOrientation(Qt::Vertical);
        QWidget *widget = new QWidget(q_ptr);
        widget->setLayout(layout);
        layout->setContentsMargins(0, 0, 0, 0);
        q_ptr->addWidget(widget);
        widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);	//设置大小策略
        layout->insertSpacerItem(0, new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
    }
    void addButton(int index, QToolButton *bt)
    {
        QLayoutItem * spacer = layout->takeAt(layout->count()-1);
        if(index < layout->count())
        {
            layout->insertWidget(index, bt);
        }
        else
        {
            layout->addWidget(bt);
        }
        buttonGroup->addButton(bt, index);
        layout->addItem(spacer);
    }
    QButtonGroup *buttonGroup = nullptr;
    ICentralWidget *centralWidget = nullptr;
    QMenu *contextMenu = nullptr;
private:
    QVBoxLayout *layout = new QVBoxLayout;
    ToolBar *q_ptr = nullptr;

};

ToolBar::ToolBar():
    m_p(new ToolBarPrivate(this))
{
    setContextMenuPolicy(Qt::DefaultContextMenu);

    connect(PluginManager::instance(), &PluginManager::pluginsLoaded, this, [this](){
        if(!m_p->buttonGroup->buttons().isEmpty())
            m_p->buttonGroup->button(0)->click();
    });

    m_p->contextMenu->setTitle(tr("Tool Bar"));
    m_p->contextMenu->addAction(tr("Show/Hide"), this, &ToolBar::toolBarShowOrHide);
    m_p->contextMenu->addAction(tr("Icons Only"), this, &ToolBar::setIconOnly);
    m_p->contextMenu->addAction(tr("Icons and Text"), this, &ToolBar::setIconAndText);

    MenuBarManager::menu<ViewMenu>()->addMenu(m_p->contextMenu);

}

void ToolBar::setCentralWidget(ICentralWidget *centralWidget)
{
    if(m_p->centralWidget)
    {
        QAbstractButton::disconnect(m_p->buttonGroup, &QButtonGroup::idClicked,
                                    m_p->centralWidget, &QTabWidget::setCurrentIndex);
    }
    m_p->centralWidget = centralWidget;
    if(m_p->centralWidget)
    {
        QAbstractButton::connect(m_p->buttonGroup, &QButtonGroup::idClicked,
                                 m_p->centralWidget, &QTabWidget::setCurrentIndex);
    }
}

QAction *ToolBar::addAction(IWidget *page)
{
    QToolButton *toolButton = new QToolButton;

    QAction *action = new QAction(page->icon(), page->windowTitle());
    action->setCheckable(true);

    toolButton->setDefaultAction(action);
    connect(this, &ToolBar::toolButtonStyleChanged, toolButton, &QToolButton::setToolButtonStyle);
    toolButton->setToolButtonStyle(toolButtonStyle());
    toolButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    toolButton->setIconSize(QSize(25, 25));
    m_p->addButton(page->index(), toolButton);
    return toolButton->defaultAction();
}

void ToolBar::contextMenuEvent(QContextMenuEvent *event)
{
    m_p->contextMenu->exec(event->globalPos());
}

void ToolBar::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    emit ToolBarMgr->toolBarSizeChanged(size());
}

void ToolBar::toolBarShowOrHide()
{
    setVisible(!isVisible());
}

void ToolBar::setIconOnly()
{
    setVisible(true);
    setToolButtonStyle(Qt::ToolButtonIconOnly);
}

void ToolBar::setIconAndText()
{
    setVisible(true);
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void ToolBarManager::setActiveWidget(int index)
{
    ToolBarMgr->m_p->toolBar->m_p->buttonGroup->button(index)->click();
}

void ToolBarManager::setVisible(bool visible)
{
    ToolBarMgr->m_p->toolBar->setVisible(visible);
}

bool ToolBarManager::isVisible()
{
    return ToolBarMgr->m_p->toolBar->isVisible();
}

void ToolBarManager::bindWidget(IWidget *page)
{
    ToolBarMgr->m_p->actions.insert(page->index(),ToolBarMgr->m_p->toolBar->addAction(page));
    ToolBarMgr->m_p->centralWidget->insertTab(page->index(), page, page->windowTitle());
}

void ToolBarManager::setUpToolBar()
{
    IWindow::setToolBar(Qt::ToolBarArea::LeftToolBarArea, ToolBarMgr->m_p->toolBar);
}

QSize ToolBarManager::size()
{
    return ToolBarMgr->m_p->toolBar->size();
}

void ToolBarManager::destroy()
{
    qDebug() << "ToolBarManager::destroy";
    delete ToolBarMgr;
}
