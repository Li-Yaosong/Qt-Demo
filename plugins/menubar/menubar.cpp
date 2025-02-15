#include "menubar.h"
#include "qapplication.h"
#include "qstyle.h"
// #include "qabstractspinbox.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <iwindow.h>
class MenuBarPrivate
{
public:
    MenuBarPrivate(MenuBar *q)
        : q_ptr(q)
    {
        Q_UNUSED(q_ptr)
    }
private:
    MenuBar *q_ptr = nullptr;
};
MenuBar::MenuBar()
    : QMenuBar{}
    , m_p(new MenuBarPrivate(this))
{

    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setCornerWidget(spacer, Qt::TopRightCorner);

    QWidget *groupBox = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(groupBox);
    groupBox->setLayout(layout);
    groupBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    layout->setContentsMargins(10, 0, 10, 0);
    layout->setSpacing(0);

    QPushButton *minimizeButton = new QPushButton(this);
    minimizeButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_TitleBarMinButton));
    minimizeButton->setIconSize(QSize(13, 13));
    minimizeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    minimizeButton->setMinimumSize(minimizeButton->iconSize() * 2);
    minimizeButton->setMaximumSize(minimizeButton->iconSize() * 2);
    connect(minimizeButton, &QPushButton::clicked, this, []() {
        IWindow::showMinWindow();
    });
    layout->addWidget(minimizeButton);

    QPushButton *closeButton = new QPushButton(this);
    closeButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    closeButton->setIconSize(QSize(13, 13));
    closeButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    closeButton->setMinimumSize(closeButton->iconSize() * 2);
    closeButton->setMaximumSize(closeButton->iconSize() * 2);
    connect(closeButton, &QPushButton::clicked, this, []() {
        IWindow::closeWindow();
    });
    layout->addWidget(closeButton);

    setCornerWidget(groupBox, Qt::TopRightCorner);
}
