#include "terminaltabwidget.h"
#include <QDebug>
TerminalTabWidget::TerminalTabWidget(QWidget *parent)
    : QTabWidget(parent)
{

}

void TerminalTabWidget::resizeEvent(QResizeEvent *event)
{
    QTabWidget::resizeEvent(event);
}
