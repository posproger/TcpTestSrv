#ifndef MTESTTHREAD_H
#define MTESTTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QByteArray>
#include "qlclientnetmanager.h"

class MTestThread : public QThread
{
    Q_OBJECT
public:
    MTestThread(qintptr socketDescriptor);
    ~MTestThread();

signals:

protected:
    void run();

public slots:
    void newBinMsgFromClient(QByteArray in);
    void socketDisconnected();

private:
    qintptr m_socketDescriptor;
    QTcpSocket * m_socket;
    QLClientNetManager * m_netManager;

};

#endif // MTESTTHREAD_H
