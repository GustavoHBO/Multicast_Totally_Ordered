#include <iostream>
#include "Multicast.hpp"
#include "Chat.hpp"
#include "Teste.hpp"

void Teste::teste_00()
{
    char msg[] = "Testando a execução";
    char ip[] = "224.0.0.1";
    Multicast m(ip, 65534);
    m.sendMessage(msg);
}

void Teste::teste_01()
{
    Chat c;
    std::cout << c.getMessage << std::endl;
}