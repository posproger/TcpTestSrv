#include "mtestcore.h"

MTestCore::MTestCore() {
    m_server = new MTestServer();
    connect(this,SIGNAL(checkStatistics()),m_server,SLOT(checkStatisticsSlot()));
}

MTestCore::~MTestCore() {
    if ( m_server ) delete(m_server);
    deleteLater();
    quit();
    wait();
}

void MTestCore::run() {
    exec();
}

void MTestCore::checkStatisticsSlot(void) {
    emit checkStatistics();
}
