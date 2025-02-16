#include "filemenu.h"
#include "iwindow.h"
#include <QStyle>
#include <QApplication>
#include <QFileDialog>
FileMenu::FileMenu(QWidget *parent)
    :IMenu(parent)
{
    IMenuFactory::registerMenu(this);
    setTitle(tr("&File"));
    QAction *openAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_DialogOpenButton),
                                      tr("&Open"), this);
    openAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    IWindow::instance()->addAction(openAction);
    connect(openAction, &QAction::triggered, this, &FileMenu::onOpenFile);
    addAction(openAction);

    QAction *saveAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_DialogSaveButton),
                                      tr("&Save"), this);
    saveAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    IWindow::instance()->addAction(saveAction);
    connect(saveAction, &QAction::triggered, this, &FileMenu::onSaveFile);
    addAction(saveAction);
    QAction *exitAction = new QAction(QApplication::style()->standardIcon(QStyle::SP_TitleBarCloseButton),
                                      tr("&Exit"), this);
    exitAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));
    IWindow::instance()->addAction(exitAction);
    connect(exitAction, &QAction::triggered, IWindow::instance(), &IWindow::close);
    addAction(exitAction);
}

QString FileMenu::type()
{
    return metaObject()->className();
}

void FileMenu::onOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(IWindow::instance(), tr("Open File"),
                                                    QDir::homePath(),
                                                    tr("All Files (*.*)"));
    IWindow::instance()->activateWindow();
    if (fileName.isEmpty())
    {
        return;
    }
    m_file.setFileName(fileName);
    emit sendFile(m_file);
}

void FileMenu::onSaveFile()
{
    emit saveFile(m_file);
}
