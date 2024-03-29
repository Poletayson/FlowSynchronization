#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QVariant>


class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = nullptr);
    Message (const int t, const QVariant &value, QObject *parent = nullptr);
    Message (const Message &other);
    enum types {EMPTY = 1, MAKE_ORDER, ORDER_TRANSFER, MATERIALS_REQUEST, MATERIALS_ARE, MATERIALS_ARE_NOT, REJECTION, ORDER_COMPLETE, MONEY_TRANSFER, CANCEL};

    QVariant getMessage() const;
    void setMessage(const QVariant &value);

    int getType() const;
    void setType(int value);
    static const int DELAY = 50;

signals:

public slots:
private:
    QVariant message;
    int type;
};

#endif // MESSAGE_H
