#include "scheduler.h"


Scheduler::Scheduler(Ad7992* ad7992, DataManager* data)
{
    m_data = data;
    m_ad7992 = ad7992;

    m_timer = new QTimer;
    connect(m_timer, &QTimer::timeout, this, &Scheduler::polling);
    m_timer->setInterval(100);
}

Scheduler::~Scheduler(){

    delete m_timer;
}

void Scheduler::start(){
    m_timer->start();
}

void Scheduler::setRefreshInterval(quint32 value){
    m_timer->setInterval(value);
}

void Scheduler::polling(){
    quint16 measuredValue = 0;
    if(m_ad7992->getValue(&measuredValue)){
        m_data->setMeasuredValue(measuredValue);
    }
    else{
        qDebug() << "Scheduler getmeasuredValue failed";
    }
}
