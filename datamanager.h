#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <qglobal.h>
#include <qobject.h>
#include <qqueue.h>

class DataManager : public QObject
{
    Q_OBJECT
public:
    DataManager();
    ~DataManager();

    quint32 getMeasuredValue()      const { return measuredValue; }
    quint32 getDisplayValue()       const { return displayValue; }
    quint32 getUpperLimit()         const { return upperLimit; }
    quint32 getLowerLimit()         const { return lowerLimit; }
    quint32 getCompensationValue()  const { return compensationValue; }
    quint32 getUpperLimitAlarm()    const { return upperLimitAlarm; }
    quint32 getLowerLimitAlarm()    const { return lowerLimitAlarm; }
    quint32 getPeakValue()          const { return peakValue; }
    quint32 getValleyValue()        const { return valleyValue; }

    QQueue<quint32> getDataQueue()  const { return dataQueue; }

public slots:
    void doReset();//reset all
    void doClear();//clear main page

    void setMeasuredValue(quint32 value);
    void setUpperLimit(quint32 value);
    void setLowerLimit(quint32 value);
    void setCompensationValue(quint32 value);
    void setQueueLength(quint32 value);

signals:
    void dataChanged();

private:
    quint32 measuredValue;
    quint32 displayValue;
    quint32 upperLimit;
    quint32 lowerLimit;
    quint32 compensationValue;
    quint32 peakValue;
    quint32 valleyValue;
    quint32 queueLength;

    QQueue<quint32> dataQueue;

    bool upperLimitAlarm;
    bool lowerLimitAlarm;

    void updateDisplayValue();
    void updateUpperLimitAlarm();
    void updateLowerLimitAlarm();
    void updatePeakValue();
    void updateValleyValue();
    void updateQueue(quint32 value);
};

#endif // DATAMANAGER_H
