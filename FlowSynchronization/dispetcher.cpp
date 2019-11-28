#include "dispetcher.h"

Dispetcher::Dispetcher(QObject *parent) : QObject(parent)
{
    customerCanal = new QCanal("customerCanal");
    dispatcherCanalOrder = new QCanal("dispatcherCanalOrder");
    courierCanal = new QCanal("courierCanal");
    generalCanal = new QCanal("generalCanal");
    dispatcherCanalToMaster = new QCanal("dispatcherCanalToMaster");
}

void Dispetcher::run()
{
     //ORDER_COUNT;
    for (int counter = 0; counter < ORDER_COUNT; counter++) {
        while (!dispatcherCanalOrder->getIsEmpty());    //ждем пока не станет можно
        dispatcherCanalOrder->put(Message::MAKE_ORDER, QVariant("Стул"));   //делаем заказ
        toFile("заказал стул");
        customerCanal->unlock();
        while (customerCanal->getIsEmpty());    //пока не станет можно

    }
}

void Dispetcher::toFile(QString str)
{
    QFile File ("out.txt");
    while (!File.open(QFile::Append));
    QTextStream stream (&File);
    stream <<"Диспетчер: " + str + "\n";
    File.close();
}
