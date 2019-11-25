#include "qcanal.h"

QCanal::QCanal():QSharedMemory()
{
    isEmpty = true;
}

QCanal::QCanal(QString key):QSharedMemory(key)
{
    isEmpty = true;
    if (!create(2048))  //создаем, либо подключаемся
        attach();
}

bool QCanal::put(int type, QVariant value)
{
    if (isEmpty){
        lock();
        //message = Message (type, value);
        isEmpty = false;
        void *dataPointer = data();
        ((int*)dataPointer)[0] = type;
        memcpy(type, dataPointer, 0);
        unlock();
        return true;
    }
    else {
        return false;
    }
}

Message QCanal::get()
{
    return message;
}

void QCanal::lock()
{
    isEmpty = false;
}

void QCanal::unlock()
{
    isEmpty = true;
}

bool QCanal::getIsEmpty() const
{
    return isEmpty;
}
