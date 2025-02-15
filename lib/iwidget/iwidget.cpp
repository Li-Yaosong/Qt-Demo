#include "iwidget.h"

#include <QBoxLayout>
class IWidgetPrivate
{
public:
    IWidgetPrivate(QWidget *w = nullptr):widget(w){}
    QWidget *widget = nullptr;
    QBoxLayout *layout = nullptr;
};

IWidget::IWidget(QWidget *parent) : QWidget{parent}
{

}

IWidget::~IWidget()
{
    m_p ? delete m_p : void();
}
