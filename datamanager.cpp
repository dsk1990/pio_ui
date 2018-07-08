#include "datamanager.h"

DataManager::DataManager()
{
    clear();
}

DataManager::~DataManager()
{

}

void DataManager::clear()
{
    measuredValue = 0;
    displayValue = 0;
    upperLimit = 0;
    lowerLimit = 0;
    compensationValue = 0;
    upperLimitAlarm = false;
    lowerLimitAlarm = false;
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
}

void DataManager::updateUpperLimitAlarm(){
    upperLimitAlarm = displayValue > upperLimit;
}

void DataManager::updateLowerLimitAlarm(){
    lowerLimitAlarm = displayValue < lowerLimit;
}
