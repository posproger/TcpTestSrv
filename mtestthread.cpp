#include "mtestthread.h"
#include "at_shared.h"

MTestThread::MTestThread(qintptr socketDescriptor) {
    m_socketDescriptor = socketDescriptor;
    m_netManager = new QLClientNetManager(0, 0, this);
    connect(m_netManager,SIGNAL(newBinaryMessageReceived(QByteArray)),this,SLOT(newBinMsgFromClient(QByteArray)));
    connect(m_netManager,SIGNAL(socketDisconnected()),this,SLOT(socketDisconnected()));
    connect(m_netManager,SIGNAL(binaryMessageSent(quint32)),this,SLOT(binaryMessageSent(quint32)));

    m_err = 0;
    m_count = 0;

    m_packetN = 1000000;
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

    QByteArray zz1;
    for ( int i=0; i<60; ++i ) { // 60000
        zz1.append("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\r\n");
    }

    if ( in.size()!=zz.size() ) {
        ++m_err;
        qlDebug() << "Size incorrect!" << in.size() << zz.size() << m_err;
//        QByteArray zz1;
//        for ( int i=0; i<60000; ++i ) {
//            zz1.append("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\r\n");
//        }
        m_netManager->sendBinaryMessage(zz1, m_packetN++);
    } else {
        m_netManager->sendBinaryMessage(in, m_packetN++);
    }
    if ( in != zz1) {
        ++m_err;
        qlDebug() << "Packet incorrect!" << qChecksum(in.constData(),in.size()) << qChecksum(zz1.constData(),zz1.size()) << m_err;
    }
}

void MTestThread::socketDisconnected() {
    ;
}

void MTestThread::checkStatistics(void) {
    qlDebug() << "Total:" << m_count << "Errors:" << m_err;
}

void MTestThread::binaryMessageSent(quint32 packetN) {
    qlDebug() << packetN << QDateTime::currentDateTime();
}

