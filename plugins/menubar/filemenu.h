#ifndef FILEMENU_H
#define FILEMENU_H
#include "menubar_global.h"
#include <imenu.h>
#include <QFile>

class MENUBAR_EXPORT FileMenu : public IMenu
{
    Q_OBJECT
public:
    explicit FileMenu(QWidget *parent = nullptr);
    virtual QString  type() final;
Q_SIGNALS:
    void sendFile(QFile &file);
    void saveFile(QFile &file);
private Q_SLOTS:
    void onOpenFile();
    void onSaveFile();
private:
    QFile m_file;
};

#endif // FILEMENU_H
