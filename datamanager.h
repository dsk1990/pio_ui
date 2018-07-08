#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <qglobal.h>
#include <qobject.h>

class DataManager : public QObject
{
    Q_OBJECT
public:
    DataManager();
    ~DataManager();

    quint32 getMeasuredValue() const { return measuredValue; }
    quint32 getDisplayValue() const { return displayValue; }
    quint32 getUpperLimit() const { return upperLimit; }
    quint32 getLowerLimit() const { return lowerLimit; }
    quint32 getCompensationValue() const { return compensationValue; }
    quint32 getUpperLimitAlarm() const { return upperLimitAlarm; }
    quint32 getLowerLimitAlarm() const { return lowerLimitAlarm; }

public slots:
    void setMeasuredValue(quint32 value);
    void setUpperLimit(quint32 value);
    void setLowerLimit(quint32 value);
    void setCompensationValue(quint32 value);

    void clear();

signals:
    void dataChanged();

private:
    quint32 measuredValue;
    quint32 displayValue;
    quint32 upperLimit;
    quint32 lowerLimit;
    quint32 compensationValue;

    bool upperLimitAlarm;
    bool lowerLimitAlarm;

    void updateDisplayValue();
    void updateUpperLimitAlarm();
    void updateLowerLimitAlarm();
};

#endif // DATAMANAGER_H
