#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QObject>
#include <QSharedMemory>
#include <QFile>
#include <QFileDevice>
#include <qcanal.h>
#include <message.h>
#include <QTextStream>

class Customer : public QObject
{
    Q_OBJECT
public:
    explicit Customer(QObject *parent = nullptr);   
    void toFile (QString str);

public slots:
    void run ();

private:
    QCanal *customerCanal;
    QCanal *dispatcherCanalOrder;
    QCanal *courierCanal;
    QCanal *generalCanal;

    int ORDER_COUNT = 100;


signals:
    void finished();


};

#endif // CUSTOMER_H
