#ifndef IWINDOW_H
#define IWINDOW_H
#include "iwidget_global.h"

#include <QMainWindow>

#include "defstruct.h"
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
    static void addCentralWidget(QWidget *widget);
    static void addStatusBar(QStatusBar *statusBar);
};

#endif // IWINDOW_H
