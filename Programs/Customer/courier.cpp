#include "courier.h"

Courier::Courier(QObject *parent) : QObject(parent)
{
    customerCanal = new QCanal("customerCanal");
    dispatcherCanalOrder = new QCanal("dispatcherCanalOrder");
    courierCanal = new QCanal("courierCanal");
    masterCanal = new QCanal("masterCanal");
    generalCanal = new QCanal("generalCanal");
    dispatcherCanalToMaster = new QCanal("dispatcherCanalToMaster");
}


void Courier::run()
{
    while (true) {
        //пока в канал мастера не поступит заказ
        while (courierCanal->getIsEmpty()); //пока ничего не поступило
        QThread::msleep(Message::DELAY);

        if (courierCanal->get().getType() == Message::ORDER_COMPLETE){
            toFile("получил заказ");
            courierCanal->unlockCanal();    //опустошаем канал
            customerCanal->put(Message::ORDER_COMPLETE, QVariant("Стул"));    //сообщает покупателю
            toFile("передал заказ");
            while (courierCanal->getIsEmpty()); //пока ничего не поступило
            QThread::msleep(Message::DELAY);
            if (courierCanal->get().getType() == Message::MONEY_TRANSFER){
                toFile("получил деньги");
                courierCanal->unlockCanal();    //опустошаем канал

                dispatcherCanalOrder->put(Message::MONEY_TRANSFER, QVariant(""));    //передаем деньги диспетчеру
                toFile("передал деньги");
            }
            else{
                toFile("Что-то не то");
            }
        }
        else{
            toFile("Что-то не то");
        }

    }

}

void Courier::toFile(QString str)
{
    QFile File ("out.txt");
    while (!File.open(QFile::Append));
    QTextStream stream (&File);
    stream <<"Курьер: " + str + "\n";
    File.close();
}
