#include <iostream>
#include "Multicast.hpp"
#include "Chat.hpp"
#include "Teste.hpp"
#include "View.hpp"

Teste::Teste()
{
}

Teste::~Teste()
{
}

void Teste::teste_00()
{
    char msg[] = "Testando a execução";
    char ip[] = "224.0.0.1";
    Multicast m(ip, 65534);
    while (true)
    {
        std::cin >> msg;
        m.send_message(msg);
        std::cout << "Enviando a mensagem: " << msg << std::endl;
    }
}

void Teste::teste_01()
{
    char ip[] = "224.0.0.1";
    Multicast m(ip, 65534);
    while (true)
    {
        std::cout << "Recebida a mensagem: " << m.receive_message() << std::endl;
    }
}

void Teste::teste_02()
{
    Chat c;
    Message m;
    char msg[] = "Teste de mensagem";
    m.set_message(msg);
    c.add_message(m);
    std::cout << c.get_message(0)->get_message() << std::endl;
}

void Teste::teste_03(int argc, char *argv[])
{
    View v(argc, argv);
}

void Teste::teste_04(int argc, char *argv[])
{
    char ip[] = "224.0.0.1";
    Chat c(ip, 65534);
    Message m;
    char msg[] = "teste de mensagem";
    m.set_message(msg);
    std::cout << "ok" << std::endl;

    c.send_message(m);
}

void Teste::teste_05()
{
    char ip[] = "224.0.0.1";
    Chat c(ip, 65534);
    c.receive_message();
}