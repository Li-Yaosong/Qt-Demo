#ifndef IWINDOW_H
#define IWINDOW_H
#include "iwidget_global.h"

#include <QMainWindow>

#include "defstruct.h"
class ICentralWidget;
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
Q_SIGNALS:
    void resizeWindow(const QSize &);
    void resizeCentralWidget(const QSize &);
    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);


};

#endif // IWINDOW_H
