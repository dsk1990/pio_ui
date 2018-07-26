#include "datamanager.h"

DataManager::DataManager()
{
    doClear();
}

DataManager::~DataManager()
{

}

void DataManager::doClear()
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

void DataManager::updateDisplayValue(){
    displayValue = measuredValue + compensationValue;
    updateUpperLimitAlarm();
    updateLowerLimitAlarm();
    updatePeakValue();
    updateValleyValue();
}

void DataManager::updateUpperLimitAlarm(){
    upperLimitAlarm = displayValue > upperLimit;
}

void DataManager::updateLowerLimitAlarm(){
    lowerLimitAlarm = displayValue < lowerLimit;
}

void DataManager::updatePeakValue(){
    if(displayValue > peakValue){
        peakValue = displayValue;
    }
}

void DataManager::updateValleyValue(){
    if(displayValue < valleyValue){
        valleyValue = displayValue;
    }
}

