#include "storage.h"

Storage::Storage(QObject *parent) : QObject(parent)
{
    customerCanal = new QCanal("customerCanal");
    dispatcherCanalOrder = new QCanal("dispatcherCanalOrder");
    courierCanal = new QCanal("courierCanal");
    generalCanal = new QCanal("generalCanal");
    storageCanal = new QCanal("storageCanal");
}


void Storage::run()
{
    while (true) {
        while (storageCanal->get().getType() != Message::MATERIALS_REQUEST);    //ждем пока не закажут материалы
        QThread::msleep(20);
        if (count >= NEED){
            count -= NEED;
            storageCanal->put(Message::MATERIALS_ARE, QVariant(""));    //передает материалы мастеру
            toFile("передал материалы. Осталось: " + QString::number(count));
        }
        else{
            storageCanal->put(Message::MATERIALS_ARE_NOT, QVariant(""));    //передает отказ
            toFile("материалов недостаточно");
        }
    }
}

void Storage::toFile(QString str)
{
    QFile File ("out.txt");
    while (!File.open(QFile::Append));
    QTextStream stream (&File);
    stream <<"Склад: " + str + "\n";
    File.close();
}
