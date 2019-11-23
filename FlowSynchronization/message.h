#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QVariant>


class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QObject *parent = nullptr);
    enum types {MAKE_ORDER = 1};

    QVariant getMessage() const;
    void setMessage(const QVariant &value);

    int getType() const;
    void setType(int value);

signals:

public slots:
private:
    QVariant message;
    int type;
};

#endif // MESSAGE_H
