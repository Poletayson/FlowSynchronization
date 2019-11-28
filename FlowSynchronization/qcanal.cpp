#include "qcanal.h"

QCanal::QCanal():QSharedMemory()
{
    isEmpty = true;
}

QCanal::QCanal(QString key):QSharedMemory(key)
{
    isEmpty = true; //и
    create(2048);
    attach();
//    if (!create(2048))  //создаем, либо подключаемся
//        attach();
}

bool QCanal::put(int type, QVariant value)
{
    if (isEmpty){
        lock();
        //message = Message (type, value);
        isEmpty = false;
        void *dataPointer = data();
        ((int*)dataPointer)[0] = type;
        memcpy (dataPointer, &value, 200);
        return true;
    }
    else {
        return false;
    }
}

Message QCanal::get()
{
    void *dataPointer = data();
    QString str = ((QString*)dataPointer)[1];
    return Message (((int*)dataPointer)[0], str);
}

void QCanal::lock()
{
    isEmpty = false;
    QSharedMemory::lock();
}

void QCanal::unlock()
{
    isEmpty = true;
    QSharedMemory::unlock();
}

bool QCanal::getIsEmpty() const
{
    return isEmpty;
}
