#include "toolbarmanager.h"
#include <QToolBar>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QToolButton>
#include <QTabWidget>
#include <QTabBar>
#include "iwindow.h"
#include "iwidget.h"
#include "pluginmanager.h"
#include "qevent.h"
#include "qmenu.h"
#include "menubarmanager.h"
#include "viewmenu.h"
InstancePtr(ToolBarManager)
class ToolBarManagerPrivate
{
public:
    ToolBarManagerPrivate()
        :toolBar(new ToolBar),
        tabWidget(new QTabWidget)
    {
        QTabBar *tabBar = tabWidget->tabBar();
        tabBar->hide();
        toolBar->setTable(tabWidget);
        IWindow::addCentralWidget(tabWidget);
    }
    ToolBar *toolBar = nullptr;
    QTabWidget *tabWidget = nullptr;
    QHash<int, QAction *> actions;
};

ToolBarManager::ToolBarManager()
    :m_p(new ToolBarManagerPrivate)
{

}
ToolBarManager::~ToolBarManager()
{

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
    QTabWidget *tabWidget = nullptr;
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

void ToolBar::setTable(QTabWidget *tabWidget)
{
    if(m_p->tabWidget)
    {
        QAbstractButton::disconnect(m_p->buttonGroup, &QButtonGroup::idClicked, m_p->tabWidget, &QTabWidget::setCurrentIndex);
    }
    m_p->tabWidget = tabWidget;
    if(m_p->tabWidget)
    {
        QAbstractButton::connect(m_p->buttonGroup, &QButtonGroup::idClicked, m_p->tabWidget, &QTabWidget::setCurrentIndex);
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

ToolBar *ToolBarManager::toolBar()
{
    return m_p->toolBar;
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
    ToolBarMgr->m_p->tabWidget->insertTab(page->index(), page, page->windowTitle());
}

void ToolBarManager::setUpToolBar()
{
    IWindow::setToolBar(Qt::ToolBarArea::LeftToolBarArea, ToolBarMgr->toolBar());
}
