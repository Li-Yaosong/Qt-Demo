#ifndef WIDGET_H
#define WIDGET_H

#include <QTabWidget>

class QTcpSocket;

class RemoteTerm : public QTabWidget
{
    Q_OBJECT
public:
    RemoteTerm(QWidget *parent = nullptr);
public slots:
     void atError();
private:
    QTcpSocket *socket;
};

#endif // WIDGET_H
