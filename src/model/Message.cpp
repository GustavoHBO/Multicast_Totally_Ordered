#include "Message.hpp"

Message::Message(/* args */)
{
}

Message::~Message()
{
}

void Message::setSender(char *sender)
{
    this->sender = sender;
}

char *Message::getSender()
{
    return this->sender;
}

void Message::setDestination(char *destination)
{
    this->destination = destination;
}

char *Message::getDestination()
{
    return this->destination;
}

void Message::setMessage(char *message)
{
    this->message = message;
}

char *Message::getMessage()
{
    return this->message;
}

void Message::setMessage(char *message)
{
    this->message = message;
}

char *Message::getMessage()
{
    return this->message;
}