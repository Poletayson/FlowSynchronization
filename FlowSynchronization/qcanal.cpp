#include "qcanal.h"

QCanal::QCanal():QSharedMemory()
{
    isEmpty = true;
}

QCanal::QCanal(QString key):QSharedMemory(key)
{

    isEmpty = true;
}

bool QCanal::put(int type, QVariant value)
{
    if (isEmpty){
        message = new Message (type, value);
        isEmpty = false;
        return true;
    }
    else {
        return false;
    }
}

Message *QCanal::get()
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
