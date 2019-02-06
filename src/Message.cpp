#include "Message.hpp"

Message::Message(/* args */)
{
}

Message::~Message()
{
}

void Message::set_sender(char *sender)
{
    this->sender = sender;
}

char *Message::get_sender()
{
    return this->sender;
}

void Message::set_destination(char *destination)
{
    this->destination = destination;
}

char *Message::get_destination()
{
    return this->destination;
}

void Message::set_date(char *date)
{
    this->date = date;
}

char *Message::get_date()
{
    return this->date;
}

void Message::set_message(char *msg){
    this->message = msg;
}

char *Message::get_message(){
    return this->message;
}