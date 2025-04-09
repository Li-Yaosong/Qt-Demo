#ifndef TOOLBARMANAGER_H
#define TOOLBARMANAGER_H
#include "toolbar_global.h"
#include <QObject>
#include <QToolBar>
#include "defstruct.h"
class QToolBar;
class QAction;
class ICentralWidget;
class IWidget;
class ToolBarPrivate;
class TOOLBAR_EXPORT ToolBar : public QToolBar
{
    Q_OBJECT
public:
    ToolBar();
    void setCentralWidget(ICentralWidget *centralWidget);
    QAction *addAction(IWidget *page);
    void contextMenuEvent(QContextMenuEvent *event);
protected:
    void resizeEvent(QResizeEvent *event);
private Q_SLOTS:
    void toolBarShowOrHide();
    void setIconOnly();
    void setIconAndText();

private:
    friend class ToolBarManager;
    ToolBarPrivate * const m_p;
};
class IWidget;
class ToolBarManagerPrivate;
class TOOLBAR_EXPORT ToolBarManager : public QObject
{
    Q_OBJECT
    Instance(ToolBarManager)
public:
    template <typename T>
    static void registerWidget()
    {
        ToolBarManager::bindWidget(new T());
    }
    static void setActiveWidget(int index);
    static void setVisible(bool visible);
    static bool isVisible();
    static void setUpToolBar();
    static QSize size();
    static void destroy();
Q_SIGNALS:
    void toolBarSizeChanged(QSize);
private:
    static void bindWidget(IWidget *page);
    ToolBarManagerPrivate * const m_p;
};

#define ToolBarMgr  ToolBarManager::instance()
#endif // TOOLBARMANAGER_H
