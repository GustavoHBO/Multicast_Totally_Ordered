#include <iostream>
#include <thread>

#include "Chat.hpp"
#include "Multicast.hpp"

Chat::Chat()
{
    qnt_message = 0;
    operations = 0;
    server = false;
}

Chat::Chat(char ip[], int port)
{
    this->ip = ip;
    this->port = port;
    qnt_message = 0;
    server = false;
}

Chat::~Chat()
{
}

void Chat::add_message(Message m)
{
    messages[qnt_message++] = m;
}

Message *Chat::get_message(int i)
{
    if (messages.find(i) == messages.end())
    {
        return NULL;
    }
    return &messages.find(i)->second;
}

void Chat::send_message(Message m)
{
    std::cout << m.get_message() << std::endl;
    char *msg = m.get_message();
    Multicast mul(this->ip, this->port);
    mul.send_message(msg);
    //this->multicast->send_message(msg);
}

void Chat::add_operation()
{
    this->operations++;
}

long long unsigned Chat::get_operations()
{
    return this->operations;
}