#include "mtestthread.h"
#include "at_shared.h"

MTestThread::MTestThread(qintptr socketDescriptor) {
    m_socketDescriptor = socketDescriptor;
    m_netManager = new QLClientNetManager(0, 0);
    connect(m_netManager,SIGNAL(newBinaryMessageReceived(QByteArray)),this,SLOT(newBinMsgFromClient(QByteArray)));
    connect(m_netManager,SIGNAL(socketDisconnected()),this,SLOT(socketDisconnected()));

    m_err = 0;
    m_count = 0;
}

MTestThread::~MTestThread() {
    deleteLater();
    quit();
    wait();
}

void MTestThread::run() {
    QTcpSocket * m_tcpSocket = new QTcpSocket();
    qlDebug() << m_tcpSocket << m_socketDescriptor;
    if (!m_tcpSocket->setSocketDescriptor(m_socketDescriptor)) {
        qlDebug() << "ERROR! Can not make socket from descriptor!";
        return;
    }
    m_netManager->setTCPSocket(m_tcpSocket);
    exec();
}

void MTestThread::newBinMsgFromClient(QByteArray in) {
    ++m_count;
    QString zz;
    zz.append(in);
    if ( in.size()!=zz.size() ) {
        ++m_err;
        qlDebug() << "Size incorrect!" << in.size() << zz.size() << m_err;
        QByteArray zz1;
        for ( int i=0; i<60000; ++i ) {
            zz1.append("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\r\n");
        }
        m_netManager->sendBinaryMessage(zz1);
    } else {
        m_netManager->sendBinaryMessage(in);
    }
}

void MTestThread::socketDisconnected() {
    ;
}

void MTestThread::checkStatistics(void) {
    qlDebug() << "Total:" << m_count << "Errors:" << m_err;
}
