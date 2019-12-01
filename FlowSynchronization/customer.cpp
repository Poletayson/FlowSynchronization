#include "customer.h"

Customer::Customer(QObject *parent) : QObject(parent)
{
    customerCanal = new QCanal("customerCanal");
    dispatcherCanalOrder = new QCanal("dispatcherCanalOrder");
    courierCanal = new QCanal("courierCanal");
    generalCanal = new QCanal("generalCanal");
}

void Customer::run()
{
//    toFile(dispatcherCanalOrder->key() + " " + QString(dispatcherCanalOrder->isAttached()));
     //ORDER_COUNT;
    for (int counter = 0; counter < ORDER_COUNT; counter++) {
        //ждем пока канал непуст
        while (!dispatcherCanalOrder->getIsEmpty()){
            toFile("ждет когда можно сделать заказ");
            QThread::msleep(20);
        }
        dispatcherCanalOrder->put(Message::MAKE_ORDER, QVariant("Стул"));   //делаем заказ
        toFile("заказал стул");
        //customerCanal->lock();
        while (customerCanal->getIsEmpty()){
            toFile("ждет ответа");    //пока не станет можно
            QThread::msleep(20);
        }
        if (customerCanal->get().getType() == Message::REJECTION)
            toFile("получил отказ");
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
