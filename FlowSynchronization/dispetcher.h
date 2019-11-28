#ifndef DISPETCHER_H
#define DISPETCHER_H

#include <QObject>
#include <QSharedMemory>
#include <QFile>
#include <QFileDevice>
#include <qcanal.h>
#include <message.h>
#include <QTextStream>

class Dispetcher : public QObject
{
    Q_OBJECT
public:
    explicit Dispetcher(QObject *parent = nullptr);
    void toFile (QString str);

public slots:
    void run ();

private:
    QCanal *customerCanal;
    QCanal *dispatcherCanalOrder;
    QCanal *dispatcherCanalToMaster;
    QCanal *courierCanal;
    QCanal *generalCanal;


signals:
    void finished();


};

#endif // DISPETCHER_H
