#include "helpmenu.h"
#include <QStyle>
#include <QApplication>
#include <QMessageBox>
#include <iwindow.h>
#include <QVBoxLayout>
#include <QTreeView>
#include "pluginmanager.h"
#include "plugintree.h"
HelpMenu::HelpMenu(QWidget *parent)
    : IMenu(parent)
{
    IMenuFactory::registerMenu(this);
    setTitle(tr("&Help"));
    IWindow *window = IWindow::instance();
    QDialog *pluginDialog = new QDialog(window);
    pluginDialog->setVisible(false);
    QVBoxLayout *layout = new QVBoxLayout;
    pluginDialog->setLayout(layout);

    QTreeView *m_pluginTree = new QTreeView(pluginDialog);
    m_pluginTree->setModel(const_cast<PluginTreeModel *>(PluginManager::instance()->pluginTreeModel()));
    m_pluginTree->setAlternatingRowColors(true);

    layout->addWidget(m_pluginTree);
    QIcon aboutIcon = QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation);
    QFile aboutFile(":/about");
    QString aboutText;
    if (aboutFile.open(QIODevice::ReadOnly))
    {
        aboutText = QString::fromUtf8(aboutFile.readAll());
        aboutFile.close();
    }
    addAction(aboutIcon, tr("&About Plugin"), pluginDialog, &QDialog::show);
    addAction(aboutIcon, tr("&About"), this, std::bind(&QMessageBox::about, window, tr("About"), aboutText));
}

QString HelpMenu::type()
{
    return metaObject()->className();
}
