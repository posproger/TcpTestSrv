#ifndef MTESTCORE_H
#define MTESTCORE_H

#include <QObject>
#include <QThread>
#include "mtestserver.h"

class MTestCore : public QThread
{
    Q_OBJECT
public:
    MTestCore();
    ~MTestCore();

signals:
    void checkStatistics(void);

protected:
    void run();

public slots:
    void checkStatisticsSlot(void);

private:
    MTestServer * m_server;

};

#endif // MTESTCORE_H
