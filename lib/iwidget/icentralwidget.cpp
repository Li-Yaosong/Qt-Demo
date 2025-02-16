#include "icentralwidget.h"
#include <QTabBar>

ICentralWidget::ICentralWidget()
{
    tabBar()->hide();
}

void ICentralWidget::resizeEvent(QResizeEvent *event)
{
    QTabWidget::resizeEvent(event);
    emit resizeWindow(size());
}
