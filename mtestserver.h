#ifndef MTESTSERVER_H
#define MTESTSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include "mtestthread.h"

class MTestServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MTestServer(QObject *parent = 0);

signals:
    void checkStatistics(void);

protected:
    void incomingConnection(qintptr socketDescriptor);

public slots:
    void checkStatisticsSlot(void);
    void clientDisconnected(void);

private:
    QList<MTestThread*> m_clients;

};

#endif // MTESTSERVER_H
