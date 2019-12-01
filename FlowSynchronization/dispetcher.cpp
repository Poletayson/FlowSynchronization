#include "dispetcher.h"

Dispetcher::Dispetcher(QObject *parent) : QObject(parent)
{
    customerCanal = new QCanal("customerCanal");
    dispatcherCanalOrder = new QCanal("dispatcherCanalOrder");
    courierCanal = new QCanal("courierCanal");
    masterCanal = new QCanal("masterCanal");
    generalCanal = new QCanal("generalCanal");
    dispatcherCanalToMaster = new QCanal("dispatcherCanalToMaster");
}

void Dispetcher::run()
{
    //toFile(dispatcherCanalOrder->key() + " " + QString(dispatcherCanalOrder->isAttached()));

    while (true) {
        while (dispatcherCanalOrder->getIsEmpty()){
            toFile("ждет заказ");   //ждем пока не поступит заказ

        }
        if (dispatcherCanalOrder->get().getType() == Message::MAKE_ORDER){
            toFile("Получил заказ");
            while (masterCanal->get().getType() != Message::EMPTY);
            masterCanal->put(Message::MAKE_ORDER, QVariant("Стул"));    //передает заказ мастеру
            toFile("Передал заказ мастеру");
            while (masterCanal->get().getType() != Message::REJECTION && courierCanal->get().getType() != Message::MONEY_TRANSFER){
                toFile("ждет ответ");
                QThread::msleep(20);
            }   //пока не отказ
            //деньги получены
            if (courierCanal->get().getType() == Message::MONEY_TRANSFER){
                toFile("деньги получены");
            }
            else
            {
                customerCanal->put(Message::REJECTION, QVariant("Стул"));    //передаем отказ
                toFile("отказ передан заказчику");
//                QThread::msleep(15);
            }
            dispatcherCanalOrder->unlockCanal();    //готов принимать новые заказы

//            customerCanal->put(Message::CANCEL, QVariant("Стул"));    //Все, заказ выполнен

        }
        else{
            toFile("Что-то не то: ");
        }

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
