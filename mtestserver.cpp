#include "mtestserver.h"
#include "at_shared.h"

MTestServer::MTestServer(QObject *parent) :
    QTcpServer(parent)
{
    if ( listen(QHostAddress::Any,8085) ) {
        qlDebug() << "start TCP listening";
    } else {
        qlDebug() << "Error! Can NOT start TCP listening!";
    }
}

void MTestServer::incomingConnection(qintptr socketDescriptor) {
    qlDebug();
    MTestThread * client = new MTestThread(socketDescriptor);
    m_clients.append(client);
    client->moveToThread(client);
    connect(this,SIGNAL(checkStatistics()),client,SLOT(checkStatistics()));
    client->start();
}

void MTestServer::clientDisconnected(void) {
    ;
}

void MTestServer::checkStatisticsSlot(void) {
    emit checkStatistics();
}

