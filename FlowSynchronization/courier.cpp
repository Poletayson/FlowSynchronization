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
        while (masterCanal->get().getType() != Message::MAKE_ORDER) {
//            toFile("ждет заказ");  //ждет заказ
//            QThread::msleep(20);
        }

        if (masterCanal->get().getType() == Message::MAKE_ORDER){
            toFile("получил заказ");
            storageCanal->put(Message::MATERIALS_REQUEST, QVariant("Стул"));    //запрашивает у склада
            toFile("запросил материалы");
            while (storageCanal->get().getType() != Message::MATERIALS_ARE && storageCanal->get().getType() != Message::MATERIALS_ARE_NOT);
            //материалы поступили
            if (storageCanal->get().getType() == Message::MATERIALS_ARE){
                masterCanal->put(Message::ORDER_READY, QVariant("Стул"));    //заказ готов, курьер должен забрать
                toFile("передал заказ курьеру");
            }
            else {
                masterCanal->put(Message::REJECTION, QVariant("Стул"));    //передает отказ
                toFile("передал отказ");
            }


            dispatcherCanalOrder->unlockCanal();    //готов принимать новые заказы
        }
        else{
            toFile("Что-то не то: ");
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
