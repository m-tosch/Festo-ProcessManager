#ifndef FESTOCONNECTION_H
#define FESTOCONNECTION_H

#include <QtNetwork/QTcpSocket>

class FestoConnection : public QObject
{
    Q_OBJECT
private:
    QTcpSocket *tcpSocket;
    int (*procMsg)(QString);

private slots:
    int readMsg();

public:
    FestoConnection(QString address, uint16_t port, int (*func)(QString));
    int send(QString);
};

#endif // FESTOCONNECTION_H
