#ifndef IWIDGET_H
#define IWIDGET_H

#include "iwidget_global.h"
#include <QWidget>
class IWidgetPrivate;
class IWIDGET_EXPORT IWidget : public QWidget
{
    Q_OBJECT
public:
    IWidget(QWidget *parent = nullptr);
    ~IWidget();
    virtual QIcon icon() const = 0;
    virtual int index() const = 0;
protected:
    IWidgetPrivate *m_p = nullptr;
};

#endif // IWIDGET_H
