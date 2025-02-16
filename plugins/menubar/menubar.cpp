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
    QWidget *groupBox = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(groupBox);
    groupBox->setLayout(layout);

    layout->setContentsMargins(10, 5, 10, 5);
    layout->setSpacing(0);

    QPushButton *minimizeButton = new QPushButton(this);
    minimizeButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_TitleBarMinButton));
    minimizeButton->setIconSize(QSize(13, 13));

    minimizeButton->setMinimumSize(minimizeButton->iconSize() * 2);
    minimizeButton->setMaximumSize(minimizeButton->iconSize() * 2);
    connect(minimizeButton, &QPushButton::clicked, IWindow::instance(), &IWindow::showMinWindow);
    layout->addWidget(minimizeButton);

    QPushButton *closeButton = new QPushButton(this);
    closeButton->setIcon(QApplication::style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    closeButton->setIconSize(QSize(13, 13));

    closeButton->setMinimumSize(closeButton->iconSize() * 2);
    closeButton->setMaximumSize(closeButton->iconSize() * 2);
    connect(closeButton, &QPushButton::clicked, IWindow::instance(), &IWindow::closeWindow);
    layout->addWidget(closeButton);

    setCornerWidget(groupBox, Qt::TopRightCorner);
    groupBox->setVisible(false);
}
