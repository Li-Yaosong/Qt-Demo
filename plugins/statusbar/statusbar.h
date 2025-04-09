#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QStatusBar>
class QDockWidget;
class StatusBarPrivate;
class StatusBar : public QStatusBar
{
    Q_OBJECT
public:
    StatusBar();
    void bindDockWidget(QDockWidget *dockWidget, int index = -1);
    void setDefaultShowDockWidget(int index);

Q_SIGNALS:
    void dockWidgetChanged(QDockWidget *dockWidget);
    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

private:
    StatusBarPrivate * const m_p;


};

#endif // STATUSBAR_H
