#include <QCoreApplication>
#include <QDebug>
#include "festoconnection.h"
#include <iostream>
#include <QThread>

int processMsg(QString msg)
{
    qDebug() << "Get Message: " + msg;

    if(msg == "crap")
    {
        // do something ...
    }

    return 0;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FestoConnection* conn = new FestoConnection(argv[1], 9000, &processMsg); // TODO: remove hardcoded data

    QThread *t = new QThread();
    conn->moveToThread(t);
    t->start();

    QTextStream s(stdin);

    while(1)
    {
        QString msg = s.readLine();
        conn->send(msg);

        if(msg == "close")
        {
            break;
        }
    }

    conn->disconnect();
    t->deleteLater();
    conn->deleteLater();

    return a.exec();
}
