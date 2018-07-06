#include "mainwindow.h"
#include <QApplication>
#include "ch367.h"
#include "ad7992.h"
#include "datamanager.h"
#include "scheduler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CH367 ch367;
    Ad7992 ad7992;
    ad7992.init(&ch367);

    DataManager data;
    Scheduler scheduler(&ad7992, &data);

    MainWindow w(0, &data);
    w.show();

    return a.exec();
}
