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
    void run ();
    void toFile (QString str);

private:
    QCanal *customerCanal;
    QCanal *dispatcherCanalOrder;
    QCanal *courierCanal;

    int ORDER_COUNT = 100;


signals:

public slots:
};

#endif // CUSTOMER_H
