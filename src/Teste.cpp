#include <iostream>

#include "Teste.hpp"
#include "Controller.hpp"
#include "Multicast.hpp"
#include "Chat.hpp"
#include "View.hpp"

Teste::Teste()
{
}

Teste::~Teste()
{
}

void Teste::teste_00()
{
    char msg[100];
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
    // View v(argc, argv);
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
    Controller ctrl(ip, 65534);
    ctrl.receive();
}

// char msg[] = "mensagem";

void me(Message *m3)
{
    Message m;
    Message m2;
    // char msg[] = "mensagem";
    char *msg = (char *)calloc(10, sizeof(char));
    msg[0] = 'o';
    msg[1] = 'i';
    msg[2] = '\0';
    m.set_message(msg);
    m2 = m;
    std::cout << "Mensagem: '" << m.get_message() << "'" << std::endl;
    std::cout << "Mensagem: '" << m2.get_message() << "'" << std::endl;
    msg[0] = 'o';
    m2.set_message(msg);
    std::cout << "Mensagem: '" << m.get_message() << "'" << std::endl;
    std::cout << "Mensagem: '" << m.get_message() << "'" << std::endl;
    (m3)->set_message(msg);
    std::cout << "Mensagem: '" << (m3)->get_message() << "'" << std::endl;
}

void Teste::teste_06()
{
    Message m, *m_ptr;
    m_ptr = &m;
    m_ptr->set_message("eitha");
    std::cout << "Mensagem aqui: '" << m.get_message() << "'" << std::endl;
    me(&m);
    std::cout << "Mensagem aqui: '" << m.get_message() << "'" << std::endl;
}