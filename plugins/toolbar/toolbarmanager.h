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
    ToolBarPrivate * const m_p;

    // QWidget interface

};
class IWidget;
class ToolBarManagerPrivate;
class TOOLBAR_EXPORT ToolBarManager : public QObject
{
    Q_OBJECT
    Instance(ToolBarManager)
    ToolBar *toolBar();
public:
    template <typename T>
    static void registerWidget()
    {
        ToolBarManager::bindWidget(new T());
    }
    static void setVisible(bool visible);
    static bool isVisible();
    static void setUpToolBar();
    static QSize size();
Q_SIGNALS:
    void toolBarSizeChanged(QSize);
private:
    static void bindWidget(IWidget *page);
    ToolBarManagerPrivate * const m_p;
};

#define ToolBarMgr  ToolBarManager::instance()
#endif // TOOLBARMANAGER_H
