#ifndef ICENTRALWIDGET_H
#define ICENTRALWIDGET_H
#include "iwidget_global.h"
#include <QTabWidget>

class IWIDGET_EXPORT ICentralWidget : public QTabWidget
{
    Q_OBJECT
public:
    ICentralWidget();

Q_SIGNALS:
    void resizeWindow(const QSize &);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // ICENTRALWIDGET_H
