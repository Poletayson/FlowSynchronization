#ifndef STORAGE_H
#define STORAGE_H

#include <QObject>
#include <QSharedMemory>
#include <QFile>
#include <QFileDevice>
#include <qcanal.h>
#include <message.h>
#include <QTextStream>
#include <QThread>

class Storage : public QObject
{
    Q_OBJECT
public:
    explicit Storage(QObject *parent = nullptr);
    void toFile (QString str);

public slots:
    void run ();

private:
    QCanal *customerCanal;      //канал для приема заказчиком
    QCanal *dispatcherCanalOrder;   //канал для приема диспетчером
    QCanal *courierCanal;
    QCanal *generalCanal;
    QCanal *storageCanal;

    int count = 100;
    const int NEED = 10;


signals:
    void finished();
};

#endif // STORAGE_H
