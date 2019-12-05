#include "customer.h"

Customer::Customer(QObject *parent) : QObject(parent)
{
    customerCanal = new QCanal("customerCanal");
    dispatcherCanalOrder = new QCanal("dispatcherCanalOrder");
    courierCanal = new QCanal("courierCanal");
    generalCanal = new QCanal("generalCanal");
}

void Customer::run(){
//    toFile(dispatcherCanalOrder->key() + " " + QString(dispatcherCanalOrder->isAttached()));
     //ORDER_COUNT;
    for (int counter = 0; counter < ORDER_COUNT; counter++) {
        //ждем пока канал непуст
        while (!dispatcherCanalOrder->getIsEmpty());
        QThread::msleep(Message::DELAY);
        dispatcherCanalOrder->put(Message::MAKE_ORDER, QVariant("Стул"));   //делаем заказ
        toFile("\nзаказал стул");
        customerCanal->unlockCanal();

        while (customerCanal->getIsEmpty());
        QThread::msleep(Message::DELAY);
        if (customerCanal->get().getType() == Message::REJECTION)
            toFile("получил отказ");
        else if(customerCanal->get().getType() == Message::ORDER_COMPLETE){
            toFile("получил готовый заказ");
            courierCanal->put(Message::MONEY_TRANSFER, QVariant(""));   //делаем заказ
            toFile("передал деньги");
        }
        customerCanal->unlockCanal();
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
