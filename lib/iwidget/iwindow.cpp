#include "iwindow.h"

InstancePtr(IWindow)
IWindow::IWindow()
    : QMainWindow{}
{
    resize(1200, 800);
    setCentralWidget(new QWidget(this));
}
IWindow::~IWindow()
{

}

void IWindow::showWindow()
{
    IWindow::instance()->show();
}

void IWindow::showMinWindow()
{
    IWindow::instance()->showMinimized();
}

void IWindow::showMaxWindow()
{
    IWindow::instance()->showMaximized();
}

void IWindow::showFullWindow()
{
    IWindow::instance()->showFullScreen();
}

void IWindow::closeWindow()
{
    IWindow::instance()->close();
}

void IWindow::setToolBar(Qt::ToolBarArea area, QToolBar *toolbar)
{
    IWindow::instance()->addToolBar(area, toolbar);
}

void IWindow::addMenuBar(QMenuBar *menuBar)
{
    IWindow::instance()->setMenuBar(menuBar);
}

void IWindow::addCentralWidget(QWidget *widget)
{
    IWindow::instance()->setCentralWidget(widget);
}
