#ifndef IWINDOW_H
#define IWINDOW_H
#include "iwidget_global.h"

#include <QMainWindow>

#include "defstruct.h"
class ICentralWidget;
class IWindowPrivate;
class IWIDGET_EXPORT IWindow : public QMainWindow
{
    Q_OBJECT
    Instance(IWindow)
public:
    static void showWindow();
    static void showMinWindow();
    static void showMaxWindow();
    static void showFullWindow();
    static void closeWindow();
    static void setToolBar(Qt::ToolBarArea area, QToolBar *toolbar);
    static void addMenuBar(QMenuBar *menuBar);
    static void addCentralWidget(ICentralWidget *widget);
    static void addStatusBar(QStatusBar *statusBar);
#if QT_CONFIG(dockwidget)
    void addDockWidget(Qt::DockWidgetArea area, QDockWidget *dockwidget);
    void addDockWidget(Qt::DockWidgetArea area, QDockWidget *dockwidget,
                       Qt::Orientation orientation);
#endif
    void setBottomDockWidgetDefaultHeight(int height, Qt::DockWidgetArea area = Qt::BottomDockWidgetArea);
Q_SIGNALS:
    void resizeWindow(const QSize &);
    void resizeCentralWidget(const QSize &);
protected:
    void resizeEvent(QResizeEvent *event);


private:
    friend class IApplicationPrivate;
    IWindowPrivate * const m_p = nullptr;

    // QObject interface
public:
    bool event(QEvent *event);
};

#endif // IWINDOW_H
