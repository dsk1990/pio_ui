#include "mainwindow.h"
#include <QTimer>
#include "datamanager.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent, DataManager *data)
    : QMainWindow(parent)
{
    m_ui = new PioWidget(this);
    this->setCentralWidget(m_ui);

    m_data = data;

    connect(m_ui, &PioWidget::requestSetDeviation, m_data, &DataManager::setCompensationValue);
    connect(m_ui, &PioWidget::requestSetUpper, m_data, &DataManager::setUpperLimit);
    connect(m_ui, &PioWidget::requestSetLower, m_data, &DataManager::setLowerLimit);
    connect(m_ui, &PioWidget::requestDoReset, m_data, &DataManager::doClear);

    connect(m_data, &DataManager::dataChanged, this, &MainWindow::updateDataShow);
}

MainWindow::~MainWindow()
{
    //delete m_ui;
}

void MainWindow::updateDataShow()
{
    m_ui->showCurrentValue                (m_data->getMeasuredValue());
    m_ui->showDeviation                   (m_data->getCompensationValue());
    m_ui->showCurrentValuePlusDeviation   (m_data->getDisplayValue());
    m_ui->showUpper                       (m_data->getUpperLimit());
    m_ui->showLower                       (m_data->getLowerLimit());
    m_ui->showUpperAlarm                  (m_data->getUpperLimitAlarm());
    m_ui->showLowerAlarm                  (m_data->getLowerLimitAlarm());
}
