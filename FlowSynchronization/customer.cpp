#include "customer.h"

Customer::Customer(QObject *parent) : QObject(parent)
{
    customerCanal = new QCanal("customerCanal");
    dispatcherCanalOrder = new QCanal("dispatcherCanalOrder");
    courierCanal = new QCanal("courierCanal");
}

void Customer::run()
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

void Customer::toFile(QString str)
{
    QFile File ("out.txt");
    while (!File.open(QFile::Append));
    QTextStream stream (&File);
    stream <<"Заказчик: " + str + "\n";
    File.close();
}
