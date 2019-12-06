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

void Dispetcher::run(){
    while (true) {
        while (dispatcherCanalOrder->getIsEmpty());
        QThread::msleep(Message::DELAY);

        if (dispatcherCanalOrder->get().getType() == Message::MAKE_ORDER){
            toFile("Получил заказ");
            while (masterCanal->get().getType() != Message::EMPTY);
            QThread::msleep(Message::DELAY);
            //dispatcherCanalOrder->unlockCanal();
            masterCanal->put(Message::MAKE_ORDER, QVariant("Стул"));    //передает заказ мастеру
            toFile("Передал заказ мастеру");

            while (dispatcherCanalOrder->get().getType() != Message::MONEY_TRANSFER && dispatcherCanalOrder->get().getType() != Message::REJECTION); //ждем ответ
            QThread::msleep(Message::DELAY);

            if (dispatcherCanalOrder->get().getType() == Message::MONEY_TRANSFER){
                toFile("Получил деньги");
            }
            else{
                toFile(QString::number(dispatcherCanalOrder->get().getType()));
                customerCanal->put(Message::REJECTION, QVariant("Стул"));    //передаем отказ
                toFile("отказ передан заказчику");
            }
            dispatcherCanalOrder->unlockCanal();

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
