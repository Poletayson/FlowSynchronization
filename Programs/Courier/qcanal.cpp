#include "qcanal.h"

QCanal::QCanal():QSharedMemory()
{
    isEmpty = true;
    put(Message::EMPTY, QVariant (""));
}

QCanal::QCanal(QString key):QSharedMemory(key)
{
    isEmpty = true; //и
    if (create(2048))
       put(Message::EMPTY, QVariant (""));
    else
        attach();
}

bool QCanal::put(int type, QVariant value)
{
    lock();

    isEmpty = false;
    int *to = (int*)data();
    memcpy(to, &type, sizeof (int));
//        dataPointer[0] = type;
//        memcpy (dataPointer, &value, 200);
    unlock();

    return true;
//    }
//    else {
//        return false;
//    }
}

Message QCanal::get()
{
    void *dataPointer = data();
    //QString str = ((QString*)dataPointer)[1];
    return Message (((int*)dataPointer)[0], "");
}

void QCanal::lockCanal()
{

}

void QCanal::unlockCanal()
{
    put(Message::EMPTY, QVariant (""));
}

bool QCanal::getIsEmpty()
{
    attach();
    lock();
    void *dataPointer = data();
    int val = ((int*)dataPointer)[0];
    unlock();

    return val == Message::EMPTY ? true : false;

}
