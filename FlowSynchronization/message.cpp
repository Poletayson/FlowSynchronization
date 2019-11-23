#include "message.h"

Message::Message(QObject *parent) : QObject(parent)
{

}

QVariant Message::getMessage() const
{
    return message;
}

void Message::setMessage(const QVariant &value)
{
    message = value;
}

int Message::getType() const
{
    return type;
}

void Message::setType(int value)
{
    type = value;
}
