#include "ohremotepage.h"
#include "toolbarmanager.h"
#include <QStyle>
#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include "ohscreendisplay.h"
class OhRemotePagePrivate
{
public:
    explicit OhRemotePagePrivate(OhRemotePage *q)
        :screenDisplay(new OhScreenDisplay(q)),
        q_ptr{q}
    {
        Q_UNUSED(q_ptr)
    }
    OhScreenDisplay *screenDisplay = nullptr;
private:
    OhRemotePage *q_ptr;
};

OhRemotePage::OhRemotePage(IWidget *parent)
    :IWidget{parent},
    m_p(new OhRemotePagePrivate(this))
{
    setWindowTitle("Remote");
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_p->screenDisplay);
    QPushButton *btn = new QPushButton("Start ScreenCast");
    layout->addWidget(btn);
    connect(btn, &QPushButton::clicked, [this]{
        m_p->screenDisplay->startScreenCast();
    });
    setLayout(layout);
}

QIcon OhRemotePage::icon() const
{
    return QApplication::style()->standardIcon((QStyle::SP_TitleBarMenuButton));
}

int OhRemotePage::index() const
{
    return 2;
}

void OhRemotePage::setUpOhRemotePage()
{
    ToolBarManager::registerWidget<OhRemotePage>();
}
