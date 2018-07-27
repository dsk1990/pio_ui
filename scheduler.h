#ifndef Scheduler_H
#define Scheduler_H

#include <qtimer.h>
#include <QtWidgets>
#include "ad7992.h"
#include "ch367.h"
#include "datamanager.h"

class PioWidget;

class Scheduler : public QObject
{
    Q_OBJECT
public:
    Scheduler(Ad7992* ad7992, DataManager* data);
    ~Scheduler();

public slots:
    void start();
    void setRefreshInterval(quint32 value);

private:
    void polling();

    QTimer*      m_timer;
    Ad7992*      m_ad7992;
    DataManager* m_data;
};

#endif // Scheduler_H
