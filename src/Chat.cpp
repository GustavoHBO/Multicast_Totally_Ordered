#include <iostream>
#include <thread>

#include "Chat.hpp"
#include "Multicast.hpp"

Chat::Chat()
{
    qnt_message = 0;
}

Chat::Chat(char ip[], int port)
{
    this->ip = ip;
    this->port = port;
    qnt_message = 0;
}

Chat::~Chat()
{
}

void Chat::add_message(Message m)
{
    if(&m != NULL && m.get_message() != NULL)
    messages[qnt_message++] = m;
}

Message *Chat::get_message(int i)
{
    auto message = messages.find(i);
    if (message == messages.end())
    {
        // std::cout << "nao existe mensagem aqui" << std::endl;
        return NULL;
    }
    // std::cout << "existe mensagem aqui" << std::endl;
    // std::cout << message->first << std::endl;
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

void Chat::add_operation(const char *op)
{
    this->operations[this->operations.size()] = op;
}

std::map<int, const char *> Chat::get_operations()
{
    return this->operations;
}