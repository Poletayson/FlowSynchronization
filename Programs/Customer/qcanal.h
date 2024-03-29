#ifndef QCANAL_H
#define QCANAL_H

#include <QObject>
#include <QSharedMemory>
#include <message.h>

class QCanal : public QSharedMemory
{
public:
    QCanal();
    QCanal(QString key);
    bool put (int type, QVariant value);    //поместить сообщение в канал
    Message get ();       //получить сообщение из канала
    void lockCanal ();
    void unlockCanal ();
    bool getIsEmpty();

private:
    bool isEmpty;
    Message* message;   //сообщение, содержащееся в канале
};

#endif // QCANAL_H
