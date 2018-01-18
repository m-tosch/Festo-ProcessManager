#include "festoconnection.h"
#include <QDebug> 

FestoConnection::FestoConnection(QString address, uint16_t port, int (*procMsgFunc)(QString)) : tcpSocket(new QTcpSocket(this))
{
    procMsg = procMsgFunc;
    connect(tcpSocket, &QTcpSocket::readyRead, this, &FestoConnection::readMsg);
    connect(tcpSocket, &QTcpSocket::connected, this, [] () -> void {qDebug() << "Connected";});
    connect(tcpSocket, &QTcpSocket::disconnected, this, [] () -> void {qDebug() << "Disconnected";});

    tcpSocket->connectToHost(address, port);
    while(!tcpSocket->waitForConnected(30000));
}

int FestoConnection::readMsg()
{
    QByteArray data = tcpSocket->readAll();
    QString string(QString::fromUtf8(data));

    return 0;
}

int FestoConnection::send(QString msg)
{
    if(tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
    tcpSocket->write((msg).toUtf8());
    tcpSocket->flush();
    qDebug() << "Sending: " << msg;
    return tcpSocket->waitForBytesWritten();
    }

    return -1;
}
