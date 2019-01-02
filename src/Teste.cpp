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
        m.sendMessage(msg);
        std::cout << "Enviando a mensagem: " << msg << std::endl;
    }
}

void Teste::teste_01()
{
    char ip[] = "224.0.0.1";
    Multicast m(ip, 65534);
    while (true)
    {
        std::cout << "Recebida a mensagem: " << m.receiveMessage() << std::endl;
    }
}

void Teste::teste_02()
{
    Chat c;
    Message m;
    char msg[] = "Teste de mensagem";
    m.setMessage(msg);
    c.addMessage(m);
    std::cout << c.getMessage(0)->getMessage() << std::endl;
}

void Teste::teste_03(int argc, char *argv[]){
    View v;
    v.startChat(argc, argv);
}