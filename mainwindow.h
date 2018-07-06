#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "piowidget.h"
#include <QMainWindow>

class DataManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0, DataManager *data = 0);
    ~MainWindow();

private:
    PioWidget*   m_ui;
    DataManager* m_data;

    //public/private?
    void updateDataShow();
};

#endif // MAINWINDOW_H
