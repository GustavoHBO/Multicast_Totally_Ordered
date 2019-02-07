#include <thread>

#include "Controller.hpp"

Message create_message(char *data)
{
    Message m;
    std::cout << "Criando mensagem" << std::endl;
    int last = 0;
    for (int i = 4; i < strlen(data); i++)
    {
        // Search the string separator, |&|
        // The message has data separated by a string, to identify the start and end of data.
        // Ex: <10>data1|&|data2|&|
        // The first data is data1, and the second data is data2
        // Ex: <10>people|&|123|&|
        // The first data is people, and the second data is 123
        if (data[i] == '|' && data[i + 1] == '&' && data[i + 2] == '|')
        {
            // i = data start;
            // -4 = string start of the string separator and the symbol to final of string.
            //Ex: message|&|, 4 characters, 3 of the string split and 1 to symbol of the string final '/0'
            char c[i - 4]; // Remove the initial string and the string separator;
            std::cout << "Valor do i: " << i << std::endl;
            // The next for split the data removing the string separator.
            for (int j = 0; j < i - 4 - last; j++) // the condition stop in j < i -4 to remove the string split and the final character.
            {
                c[j] = data[j + 4 + last];
                c[j + 1] = '\0';// add the final character. Put an 'if' there can be more heavy.
            }
            i += 3;// Increment the i to jump next character after the string separator.
            last += strlen(c) + 3; // Save the length of data + length of the string separator.
            std::cout << "Mensagem encontrada: " << c << std::endl;
            std::cout << "Tamanho da mensagem encontrada: " << strlen(c) << std::endl;
            m.set_message(c);
        }
    }

    return m;
}

void process_data(char *data, Chat *c)
{
    std::cout << c->get_operations() << std::endl;
    std::cout << "Mensagem: \'" << data << "\'" << std::endl;
    std::cout << "Tamanho: " << strlen(data) << std::endl;

    if (strlen(data) < 3 || data[0] != '<' && data[3] != '>')
    {
        std::cout << "Dados corrompidos!" << std::endl;
        return;
    }
    else if (data[1] == '0') // Obter dados
    {
        if (data[2] == '0')
        {
            c->add_operation();

            std::cout << "Sincronizar base de dados!" << std::endl;
        }
    }
    else if (data[1] == '1') // Receber dados
    {
        Message m;
        create_message(data);
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
        std::cout << "Operação inválida!" << std::endl;
    }
}

Controller::Controller(char ip[], int port)
{
    char ip_default[] = "224.0.0.1";
    int port_default = 65534;
    this->ip = ip ? ip : ip_default;
    this->port = port ? port : port_default;
    this->chat = Chat();
}

Controller::~Controller()
{
}

Chat *Controller::get_chat()
{
    return &this->chat;
}

void Controller::receive()
{
    Multicast m(this->ip, this->port);
    while (true)
    {
        std::thread t(process_data, m.receive_message(), &this->chat);
        t.join();
    }
}
