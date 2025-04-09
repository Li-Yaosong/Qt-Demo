#include "iwindow.h"
#include "qcoreevent.h"
#include "qlayout.h"
#include "icentralwidget.h"
#include <QDockWidget>
InstancePtr(IWindow)
class IWindowPrivate
{
public:
    IWindowPrivate(IWindow *q)
        : q_ptr(q)
    {
        Q_UNUSED(q_ptr);
        // q_ptr->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, bottomDockWidget);
    }
    int dockWidgetHeight = 200;
    // QDockWidget *bottomDockWidget = nullptr;
    QList<QDockWidget *> docks;
private:
    IWindow *q_ptr = nullptr;
};

IWindow::IWindow()
    : QMainWindow{},
    m_p(new IWindowPrivate(this))
{
    resize(1200, 800);
    layout()->setSpacing(0);
}
IWindow::~IWindow()
{

}

void IWindow::showWindow()
{
    IWindow::instance()->show();
}

void IWindow::showMinWindow()
{
    IWindow::instance()->showMinimized();
}

void IWindow::showMaxWindow()
{
    IWindow::instance()->showMaximized();
}

void IWindow::showFullWindow()
{
    IWindow::instance()->showFullScreen();
}

void IWindow::closeWindow()
{
    IWindow::instance()->close();
}

void IWindow::setToolBar(Qt::ToolBarArea area, QToolBar *toolbar)
{
    IWindow::instance()->addToolBar(area, toolbar);
}

void IWindow::addMenuBar(QMenuBar *menuBar)
{
    IWindow::instance()->setMenuBar(menuBar);
}

void IWindow::addCentralWidget(ICentralWidget *widget)
{
    IWindow::instance()->setCentralWidget(widget);
    connect(widget, &ICentralWidget::resizeWindow, IWindow::instance(), &IWindow::resizeCentralWidget);
}

void IWindow::addStatusBar(QStatusBar *statusBar)
{
    IWindow::instance()->setStatusBar(statusBar);
}

void IWindow::setBottomDockWidgetDefaultHeight(int height, Qt::DockWidgetArea area)
{
    if (m_p->dockWidgetHeight != height) {
        m_p->dockWidgetHeight = height;
        for (QDockWidget *dock : std::as_const(m_p->docks)) {
            if (dock->allowedAreas() == area) {
                dock->resize(dock->width(), height);
            }
        }
    }
}

void IWindow::addDockWidget(Qt::DockWidgetArea area, QDockWidget *dockwidget)
{
    QMainWindow::addDockWidget(area, dockwidget);
    dockwidget->resize(dockwidget->width(), m_p->dockWidgetHeight);
    m_p->docks.append(dockwidget);
}

void IWindow::addDockWidget(Qt::DockWidgetArea area, QDockWidget *dockwidget, Qt::Orientation orientation)
{
    dockwidget->resize(dockwidget->width(), m_p->dockWidgetHeight);
    QMainWindow::addDockWidget(area, dockwidget, orientation);
    m_p->docks.append(dockwidget);
}

void IWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    // qDebug() << "resizeEvent" << event;
    emit resizeWindow(size());
}

bool IWindow::event(QEvent *event)
{
    if (event->type() != QEvent::UpdateRequest
        && event->type() != QEvent::Paint
        && event->type() != QEvent::MouseMove
        && event->type() != QEvent::HoverMove
        && event->type() != QEvent::Timer
        && event->type() != QEvent::MouseButtonRelease
        && event->type() != QEvent::CursorChange
        ) {
        // qDebug() << "event" << event->type();
    }
    switch (event->type()) {
        case QEvent::LayoutRequest:
        {

        }
        case QEvent::None:
        case QEvent::Timer:
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseButtonDblClick:
        case QEvent::MouseMove:
        case QEvent::KeyPress:
        case QEvent::KeyRelease:
        case QEvent::FocusIn:
        case QEvent::FocusOut:
        case QEvent::FocusAboutToChange:
        case QEvent::Enter:
        case QEvent::Leave:
        case QEvent::Paint:
        case QEvent::Move:
        case QEvent::Resize:
        case QEvent::Create:
        case QEvent::Destroy:
        case QEvent::Show:
        case QEvent::Hide:
        case QEvent::Close:
        case QEvent::Quit:
        case QEvent::ParentChange:
        case QEvent::ParentAboutToChange:
        case QEvent::ThreadChange:
        case QEvent::WindowActivate:
        case QEvent::WindowDeactivate:
        case QEvent::ShowToParent:
        case QEvent::HideToParent:
        case QEvent::Wheel:
        case QEvent::WindowTitleChange:
        case QEvent::WindowIconChange:
        case QEvent::ApplicationWindowIconChange:
        case QEvent::ApplicationFontChange:
        case QEvent::ApplicationLayoutDirectionChange:
        case QEvent::ApplicationPaletteChange:
        case QEvent::PaletteChange:
        case QEvent::Clipboard:
        case QEvent::Speech:
        case QEvent::MetaCall:
        case QEvent::SockAct:
        case QEvent::WinEventAct:
        case QEvent::DeferredDelete:
        case QEvent::DragEnter:
        case QEvent::DragMove:
        case QEvent::DragLeave:
        case QEvent::Drop:
        case QEvent::DragResponse:
        case QEvent::ChildAdded:
        case QEvent::ChildPolished:
        case QEvent::ChildRemoved:
        case QEvent::ShowWindowRequest:
        case QEvent::PolishRequest:
        case QEvent::Polish:
        case QEvent::UpdateRequest:
        case QEvent::UpdateLater:
        case QEvent::EmbeddingControl:
        case QEvent::ActivateControl:
        case QEvent::DeactivateControl:
        case QEvent::ContextMenu:
        case QEvent::InputMethod:
        case QEvent::TabletMove:
        case QEvent::LocaleChange:
        case QEvent::LanguageChange:
        case QEvent::LayoutDirectionChange:
        case QEvent::Style:
        case QEvent::TabletPress:
        case QEvent::TabletRelease:
        case QEvent::OkRequest:
        case QEvent::HelpRequest:
        case QEvent::IconDrag:
        case QEvent::FontChange:
        case QEvent::EnabledChange:
        case QEvent::ActivationChange:
        case QEvent::StyleChange:
        case QEvent::IconTextChange:
        case QEvent::ModifiedChange:
        case QEvent::MouseTrackingChange:
        case QEvent::WindowBlocked:
        case QEvent::WindowUnblocked:
        case QEvent::WindowStateChange:
        case QEvent::ReadOnlyChange:
        case QEvent::ToolTip:
        case QEvent::WhatsThis:
        case QEvent::StatusTip:
        case QEvent::ActionChanged:
        case QEvent::ActionAdded:
        case QEvent::ActionRemoved:
        case QEvent::FileOpen:
        case QEvent::Shortcut:
        case QEvent::ShortcutOverride:
        case QEvent::WhatsThisClicked:
        case QEvent::ToolBarChange:
        case QEvent::ApplicationActivate:
        case QEvent::ApplicationDeactivate:
        case QEvent::QueryWhatsThis:
        case QEvent::EnterWhatsThisMode:
        case QEvent::LeaveWhatsThisMode:
        case QEvent::ZOrderChange:
        case QEvent::HoverEnter:
        case QEvent::HoverLeave:
        case QEvent::HoverMove:
        case QEvent::AcceptDropsChange:
        case QEvent::ZeroTimerEvent:
        case QEvent::GraphicsSceneMouseMove:
        case QEvent::GraphicsSceneMousePress:
        case QEvent::GraphicsSceneMouseRelease:
        case QEvent::GraphicsSceneMouseDoubleClick:
        case QEvent::GraphicsSceneContextMenu:
        case QEvent::GraphicsSceneHoverEnter:
        case QEvent::GraphicsSceneHoverMove:
        case QEvent::GraphicsSceneHoverLeave:
        case QEvent::GraphicsSceneHelp:
        case QEvent::GraphicsSceneDragEnter:
        case QEvent::GraphicsSceneDragMove:
        case QEvent::GraphicsSceneDragLeave:
        case QEvent::GraphicsSceneDrop:
        case QEvent::GraphicsSceneWheel:
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        case QEvent::GraphicsSceneLeave:
#endif
        case QEvent::KeyboardLayoutChange:
        case QEvent::DynamicPropertyChange:
        case QEvent::TabletEnterProximity:
        case QEvent::TabletLeaveProximity:
        case QEvent::NonClientAreaMouseMove:
        case QEvent::NonClientAreaMouseButtonPress:
        case QEvent::NonClientAreaMouseButtonRelease:
        case QEvent::NonClientAreaMouseButtonDblClick:
        case QEvent::MacSizeChange:
        case QEvent::ContentsRectChange:
        case QEvent::MacGLWindowChange:
        case QEvent::FutureCallOut:
        case QEvent::GraphicsSceneResize:
        case QEvent::GraphicsSceneMove:
        case QEvent::CursorChange:
        case QEvent::ToolTipChange:
        case QEvent::NetworkReplyUpdated:
        case QEvent::GrabMouse:
        case QEvent::UngrabMouse:
        case QEvent::GrabKeyboard:
        case QEvent::UngrabKeyboard:
        case QEvent::StateMachineSignal:
        case QEvent::StateMachineWrapped:
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd:
        case QEvent::NativeGesture:
        case QEvent::RequestSoftwareInputPanel:
        case QEvent::CloseSoftwareInputPanel:
        case QEvent::WinIdChange:
        case QEvent::Gesture:
        case QEvent::GestureOverride:
        case QEvent::ScrollPrepare:
        case QEvent::Scroll:
        case QEvent::Expose:
        case QEvent::InputMethodQuery:
        case QEvent::OrientationChange:
        case QEvent::TouchCancel:
        case QEvent::ThemeChange:
        case QEvent::SockClose:
        case QEvent::PlatformPanel:
        case QEvent::StyleAnimationUpdate:
        case QEvent::ApplicationStateChange:
        case QEvent::WindowChangeInternal:
        case QEvent::ScreenChangeInternal:
        case QEvent::PlatformSurface:
        case QEvent::Pointer:
        case QEvent::TabletTrackingChange:
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        case QEvent::WindowAboutToChangeInternal:
        case QEvent::DevicePixelRatioChange:
        case QEvent::ChildWindowAdded:
        case QEvent::ChildWindowRemoved:
        case QEvent::ParentWindowAboutToChange:
        case QEvent::ParentWindowChange:
#endif
        case QEvent::User:
        case QEvent::MaxUser:
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        case QEvent::MacGLClearDrawable:
#endif
            break;
        }

    return QMainWindow::event(event);
}
