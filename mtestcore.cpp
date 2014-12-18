#include "mtestcore.h"

MTestCore::MTestCore() {
    m_server = new MTestServer();
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
