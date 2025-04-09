#include "icentralwidget.h"
#include <QTabBar>

ICentralWidget::ICentralWidget()
{
    tabBar()->hide();
}

ICentralWidget::~ICentralWidget()
{
    for (int i = 0; i < count(); ++i)
        delete widget(i);
}

void ICentralWidget::resizeEvent(QResizeEvent *event)
{
    QTabWidget::resizeEvent(event);
    emit resizeWindow(size());
}
