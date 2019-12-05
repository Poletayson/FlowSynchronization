#include "storage.h"

Storage::Storage(QObject *parent) : QObject(parent)
{
    masterCanal = new QCanal("masterCanal");
    generalCanal = new QCanal("generalCanal");
    storageCanal = new QCanal("storageCanal");
}


void Storage::run()
{
    while (true) {
        while (storageCanal->getIsEmpty());    //ждем пока не закажут материалы
        QThread::msleep(Message::DELAY);
        //заказали материалы
        if (storageCanal->get().getType() == Message::MATERIALS_REQUEST){
            toFile("поступил заказ на материалы");
            storageCanal->unlockCanal();
            if (count >= NEED){
                count -= NEED;
                masterCanal->put(Message::MATERIALS_ARE, QVariant(""));    //передает материалы мастеру
                toFile("передал материалы. Осталось: " + QString::number(count));
            }
            else{
                masterCanal->put(Message::MATERIALS_ARE_NOT, QVariant(""));    //передает отказ
                toFile("материалов недостаточно. Осталось: " + QString::number(count));
            }
        }
        else{
            toFile("Что-то не то");
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
