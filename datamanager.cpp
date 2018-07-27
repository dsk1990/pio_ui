#include "datamanager.h"
#include <algorithm>

DataManager::DataManager()
{
    doReset();
}

DataManager::~DataManager()
{

}

void DataManager::doReset()
{
    measuredValue = 0;
    displayValue = 0;
    upperLimit = 0;
    lowerLimit = 0;
    compensationValue = 0;
    upperLimitAlarm = false;
    lowerLimitAlarm = false;
    peakValue = 0;
    valleyValue = 0;

    queueLength = 1;
    dataQueue.clear();
}

void DataManager::doClear()
{
    displayValue = 0;
    upperLimitAlarm = false;
    lowerLimitAlarm = false;
    peakValue = 0;
    valleyValue = 0;

    dataQueue.clear();
}

void DataManager::setMeasuredValue(quint32 value){
    measuredValue = value;
    updateDisplayValue();
    emit dataChanged(/*enum setMeasuredValue, quint32 value*/);
}

void DataManager::setUpperLimit(quint32 value){
    upperLimit = value;
    updateUpperLimitAlarm();
    emit dataChanged();
}

void DataManager::setLowerLimit(quint32 value){
    lowerLimit = value;
    updateLowerLimitAlarm();
    emit dataChanged();
}

void DataManager::setCompensationValue(quint32 value){
    compensationValue = value;
    updateDisplayValue();
    emit dataChanged();
}

void DataManager::setQueueLength(quint32 value){
    queueLength = value;
    while((quint32)dataQueue.size() > queueLength){
        dataQueue.dequeue();
    }
    emit dataChanged();
}

void DataManager::updateDisplayValue(){
    displayValue = measuredValue + compensationValue;
    updateUpperLimitAlarm();
    updateLowerLimitAlarm();
    updateQueue(displayValue);
}

void DataManager::updateUpperLimitAlarm(){
    upperLimitAlarm = displayValue > upperLimit;
}

void DataManager::updateLowerLimitAlarm(){
    lowerLimitAlarm = displayValue < lowerLimit;
}

void DataManager::updatePeakValue(){
    if(dataQueue.size() == 1){
        peakValue = displayValue;
    }
    peakValue = std::max(peakValue, displayValue);
}

void DataManager::updateValleyValue(){
    if(dataQueue.size() == 1){
        valleyValue = displayValue;
    }
    valleyValue = std::min(valleyValue, displayValue);
}

void DataManager::updateQueue(quint32 value){
    if((quint32)dataQueue.size() >= queueLength){
        dataQueue.dequeue();
    }
    dataQueue.enqueue(value);
    updatePeakValue();
    updateValleyValue();
}
