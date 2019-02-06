#include <iostream>
#include <thread>

#include "Chat.hpp"
#include "Multicast.hpp"

void receive_data(char *data, Chat *c)
{
    if (strlen(data) < 4 && data[0] != '<' && data[3] != '>')
    {
        std::cout << "Dados corrompidos!" << strlen(data) << std::endl;
    }
    else if (data[1] == '0') // Obter dados
    {
        std::cout << "Obter todas as mensagens" << std::endl;
    }
    else if (data[1] == '1') // Receber dados
    {
        std::cout << "Nova mensagem" << std::endl;
    }
    else if (data[1] == '2') // Operações
    {
        if (data[2] == '0')
        {
            std::cout << "Nova eleição" << std::endl;
        }
        else if (data[2] == '1')
        {
            std::cout << "Verificar a existencia de um master" << std::endl;
        }
    }

    else
    {
        std::cout << "Algo de errado não está certo!" << std::endl;
    }
}

void teste1()
{
    while (true)
    {
        /* code */
        std::cout << "oie" << std::endl;
    }
}

void teste2()
{
    while (true)
    {
        /* code */
        std::cout << "123" << std::endl;
    }
}

Chat::Chat()
{
    qnt_message = 0;
    operations = 0;
    server = false;
}

Chat::Chat(char ip[], int port)
{
    char ip_default[] = "224.0.0.1";
    int port_default = 65534;
    this->ip = ip ? ip : ip_default;
    this->port = port ? port : port_default;
    qnt_message = 0;
    server = false;
    operations = 0;
    Multicast m(this->ip, this->port);
    this->multicast = Multicast(this->ip, this->port);
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
    //this->multicast->sendMessage(msg);
}

void Chat::receive_message()
{
    Multicast m(this->ip, this->port);
    while (true)
    {
        std::thread t(receive_data, m.receive_message(), this);
        t.join();
    }
}

void Chat::add_operation()
{
    this->operations++;
}

long long unsigned Chat::get_operations()
{
    return this->operations;
}