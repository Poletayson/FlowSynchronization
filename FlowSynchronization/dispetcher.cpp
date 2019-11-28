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
    toFile(dispatcherCanalOrder->key() + " " + QString(dispatcherCanalOrder->isAttached()));

    while (true) {
        while (dispatcherCanalOrder->QSharedMemory::lock())toFile("ждет заказ");   //ждем пока не поступит заказ
        if (dispatcherCanalOrder->get().getType() == Message::MAKE_ORDER){
            toFile("Получил заказ");
            dispatcherCanalOrder->unlock();    //Все, заказ выполнен
        }
        else{
            toFile("Что-то не то: ");
        }

    }


//    for (int counter = 0; counter < ORDER_COUNT; counter++) {
//        while (!dispatcherCanalOrder->getIsEmpty());    //ждем пока не станет можно
//        dispatcherCanalOrder->put(Message::MAKE_ORDER, QVariant("Стул"));   //делаем заказ
//        toFile("заказал стул");
//        customerCanal->unlock();
//        while (customerCanal->getIsEmpty());    //пока не станет можно

//    }
}

void Dispetcher::toFile(QString str)
{
    QFile File ("out.txt");
    while (!File.open(QFile::Append));
    QTextStream stream (&File);
    stream <<"Диспетчер: " + str + "\n";
    File.close();
}
