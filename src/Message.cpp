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

void Message::setDate(char *date)
{
    this->date = date;
}

char *Message::getDate()
{
    return this->date;
}

void Message::setMessage(char *msg){
    this->message = msg;
}

char *Message::getMessage(){
    return this->message;
}