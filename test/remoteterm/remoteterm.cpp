#include "remoteterm.h"
#include <QTcpSocket>
#include <QDebug>
// #include <unistd.h>

RemoteTerm::RemoteTerm(QWidget *parent)
    : QTabWidget(parent)
{
    // socket = new QTcpSocket(this);
    
    // // Write what we input to remote terminal via socket
    // connect(this, &RemoteTerm::sendData,[this](const char *data, int size){
    //     this->socket->write(data, size);
    // });

    // // Read anything from remote terminal via socket and show it on widget.
    // connect(socket,&QTcpSocket::readyRead,[this](){
    //     QByteArray data = socket->readAll();
    //     recvData(data.data(), data.size());
    // });
    // connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(atError()));

    // Here we start an empty pty.
    // this->startTerminalTeletype();

    // socket->connectToHost(ipaddr, port);
    setGeometry(100, 100, 800, 600);
}

void RemoteTerm::atError()
{
    qDebug() << socket->errorString();
}
