#include "mainwindow.h"

#include <QApplication>
#include <QThread>
#include <customer.h>
#include <dispetcher.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //создаем объекты и перемещаем в потоки
    QThread* customerThread = new QThread();
    Customer* customer = new Customer ();
    QObject::connect(customerThread,SIGNAL(started()), customer, SLOT(run()));
    QObject::connect(customer, SIGNAL(finished()), customerThread, SLOT(terminate()));
    customer->moveToThread(customerThread);

    QThread* dispetcherThread = new QThread();
    Dispetcher* dispetcher = new Dispetcher ();
    QObject::connect(dispetcherThread,SIGNAL(started()), dispetcher, SLOT(run()));
    QObject::connect(dispetcher, SIGNAL(finished()), dispetcherThread, SLOT(terminate()));
    dispetcher->moveToThread(dispetcherThread);



    MainWindow w;
    w.show();
    return a.exec();
}
