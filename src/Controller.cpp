#include <thread>

#include "Controller.hpp"

bool active = false;

/*
* This method create the message from data.
*/
void split_data(char *data, char ***data_out)
{
    std::cout << "Separando os dados: '" << data << "'" << std::endl;
    *data_out = (char **)calloc(10, sizeof(char *));
    int qt_data = 0, last = 0;
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
            // The next for split the data removing the string separator.
            for (int j = 0; j < i - 4 - last; j++) // the condition stop in j < i -4 to remove the string split and the final character.
            {
                c[j] = data[j + 4 + last];
                c[j + 1] = '\0'; // add the final character. Put an 'if' there can be more heavy.
            }
            i += 3;                                                // Increment the i to jump next character after the string separator.
            last += strlen(c) + 3;                                 // Save the length of data + length of the string separator.
            **data_out = (char *)malloc(strlen(c) * sizeof(char)); // Allocating memory to line.
            strcpy(**data_out, c);                                 // Copying the string c to string **p.
            qt_data++;                                             // set the quantity of messages.
            std::cout << **data_out << std::endl;
            if (i + 4 < strlen(data))
            {
                *data_out += sizeof(char *); // Move the pointer to next line.
            }
            else
            {
                *data_out -= sizeof(char *) * (qt_data - 1); // Move the pointer for the initial address.
            }
        }
    }
}

void process_data(char *data, Chat *c, Controller *ctrl)
{
    // std::cout << c->get_operations().size() << std::endl;
    // std::cout << "Mensagem: \'" << data << "\'" << std::endl;
    // std::cout << "Tamanho: " << strlen(data) << std::endl;

    if (strlen(data) < 3)
    {
        std::cout << "Dados corrompidos!" << std::endl;
        return;
    }
    if (data[0] == '<' && data[3] == '>')
    {
        if (data[1] == '0') // Get data
        {
            if (data[2] == '0')
            {
                //c->add_operation("00");// Not necessary add the operation of synchronization
                for (int i = 0; i < c->get_operations().size(); i++)
                {
                    const char *operation;
                    operation = c->get_operations()[i];
                    std::cout << operation << std::endl;
                    if (operation[0] == '1' && operation[1] == '0')
                    {
                        Message *m;
                        m = c->get_message(i);
                        if (m != NULL)
                        {
                            std::cout << m->get_message() << std::endl;
                        }
                    }
                }
            }
        }
        else if (data[1] == '1') // Receber dados
        {
            if (data[2] == '0')
            {
                Message m;
                char **msg;
                // std::cout << "Mensagem gravada: '" << &msg << "'" << std::endl;
                split_data(data, &msg);
                // msg += 8;
                m.set_message(*msg);
                // std::cout << "Mensagem gravada: '" << m.get_message() << "'" << std::endl;
                c->add_message(m);
                c->add_operation("10");
            }
        }
        else if (data[1] == '2') // Operações
        {
            if (data[2] == '0')
            {
                ctrl->id_master = INT32_MAX;
                std::cout << "Nova eleição : " << ctrl->get_id() << std::endl;
                char *msg = (char *)malloc(6 * sizeof(char)); // Memory to message
                msg[0] = '[';
                msg[1] = '2';
                msg[2] = '0';
                msg[3] = ']';
                msg[4] = (char)ctrl->get_id();
                msg[5] = '\0'; // Final string.
                //ctrl->set_id_count(ctrl->get_id_count() + 1);
                ctrl->send_data(msg);
            }
            else if (data[2] == '1')
            {
                if (ctrl->is_server())
                {

                    std::cout << "Verificar a existencia de um master" << std::endl;
                    char *msg = (char *)malloc(6 * sizeof(char)); // Memory to message
                    msg[0] = '[';
                    msg[1] = '2';
                    msg[2] = '1';
                    msg[3] = ']';
                    msg[4] = (char)ctrl->get_id();
                    msg[5] = '\0'; // Final string.
                    //ctrl->set_id_count(ctrl->get_id_count() + 1);
                    ctrl->send_data(msg);
                }
            }
            else if (data[2] == '2')
            { // Get new id
                char **msg_split;
                split_data(data, &msg_split);
                if (ctrl->is_server())
                {
                    std::cout << "Servidor definindo id: " << ctrl->get_id_count() + 1 << std::endl;

                    char *msg = (char *)malloc(13 * sizeof(char)); // Memory to message
                    msg[0] = '[';
                    msg[1] = '2';
                    msg[2] = '2';
                    msg[3] = ']';
                    msg[4] = msg_split[0][0];
                    msg[5] = msg_split[0][1];
                    msg[6] = msg_split[0][2];
                    msg[7] = msg_split[0][3];
                    msg[8] = (char)ctrl->get_next_id_count();
                    msg[9] = '|';
                    msg[10] = '&';
                    msg[11] = '|';
                    msg[12] = '\0'; // Final string.
                    //ctrl->set_id_count(ctrl->get_id_count() + 1);
                    ctrl->send_data(msg);
                }
            }
        }
        else if (data[1] == '3')
        {
            std::cout << "Exibir todas as mensagens!" << std::endl;
            for (int i = 0; i < ctrl->get_chat()->get_operations().size(); i++)
            {
                std::cout << "Menssagem = " << ctrl->get_chat()->get_message(i)->get_message() << std::endl;
            }
        }
        else
        {
            std::cout << "Operação inválida!" << std::endl;
        }
    }
    else if (data[0] == '[' && data[3] == ']')
    {
        if (data[1] == '2')
        {
            if (data[2] == '0')
            {
                // std::cout << "Id master atual : " << ctrl->id_master << std::endl;
                // std::cout << "Id que recebi : " << (int)data[4] << std::endl;
                // std::cout << "Meu id : " << ctrl->get_id() << std::endl;
                // std::cout << "Sou ativo? : " << active << std::endl;
                if (ctrl->id_master > (int)data[4])
                {
                    ctrl->id_master = (int)data[4];
                    if (ctrl->id_master == ctrl->get_id() && active)
                    {
                        // if (ctrl->id_master == 100)
                        // {
                        //     ctrl->id_master = 0;
                        //     ctrl->set_id(0);
                        // }
                        std::cout << "Sou o servidor! : " << ctrl->get_id() << std::endl;
                        ctrl->set_server(true);
                        ctrl->set_id_count(ctrl->id_master+1);
                    }
                    else
                    {
                        if ((int)data[4] != ctrl->get_id())
                            active = true;
                        std::cout << "Não sou o servidor! : " << (int)data[4] << std::endl;
                        ctrl->set_server(false);
                    }
                }
            }
            else if (data[2] == '1' && !ctrl->is_server())
            {
                // char *msg = (char *)malloc(6 * sizeof(char)); // Memory to message
                // msg[0] = '[';
                // msg[1] = '2';
                // msg[2] = '1';
                // msg[3] = ']';
                // msg[4] = (char)ctrl->get_id();
                // msg[5] = '\0'; // Final string.
                //ctrl->set_id_count((int)data[4] + 1);
                //ctrl->send_data(msg);
            }
            else if (data[2] == '2')
            {
                ctrl->set_id_count((int)data[8] + 1);
                // std::cout << "Alguém quer se conectar ao grupo! : " << ctrl->get_id_count() << std::endl;
            }
        }
    }
}

void server_data(Controller *ctrl)
{
    Multicast m(ctrl->get_ip(), ctrl->get_port());
    while (true)
    {
        std::thread t(process_data, m.receive_message(), ctrl->get_chat(), ctrl);
        t.join();
    }
}

Controller::Controller(char ip[], int port)
{
    char ip_default[] = "224.0.0.1";
    int port_default = 65534;
    this->server = false;
    this->id = 100;
    this->id_count = 11;
    this->ip = ip ? ip : ip_default;
    this->port = port ? port : port_default;
    this->chat = Chat();
    this->multicast = Multicast(this->ip, this->port);
    this->id_master = INT32_MAX;

    //Initializes and joins the network
    std::thread t0(server_data, this);
    if (verify_master())
    {
        std::cout << "Existe master!" << std::endl;
        char msg[12];
        char code[4];
        srand(time(NULL));
        code[0] = (char)(rand() % 91) + 48;
        code[1] = (char)(rand() % 91) + 48;
        code[2] = (char)(rand() % 91) + 48;
        code[3] = (char)(rand() % 91) + 48;

        msg[0] = '<';
        msg[1] = '2';
        msg[2] = '2';
        msg[3] = '>';

        msg[4] = code[0];
        msg[5] = code[1];
        msg[6] = code[2];
        msg[7] = code[3];

        msg[8] = '|';
        msg[9] = '&';
        msg[10] = '|';
        msg[11] = '\0';

        Multicast m(get_ip(), get_port());
        m.send_message(msg);

        char **msg_split;
        do
        {
            split_data(m.receive_message(), &msg_split);
            // std::cout << "Esperando o id: " << id << std::endl;

        } while (strlen(msg_split[0]) != 5 || msg_split[0][0] != code[0] || msg_split[0][1] != code[1] || msg_split[0][2] != code[2] || msg_split[0][3] != code[3]);
        id = (int)msg_split[0][4];
        active = true;
        std::cout << "Recebi o id: " << id << std::endl;
    }
    else
    {
        std::cout << "Não existe master!" << std::endl;
        char *msg = (char *)malloc(5 * sizeof(char)); // Memory to message
        msg[0] = '<';
        msg[1] = '2';
        msg[2] = '0';
        msg[3] = '>';
        // msg[4] = (char)255;
        msg[4] = '\0'; // Final string.
        // set_id_count(0);
        send_data(msg);
        sleep(5);
        if (!active)
        {
            server = true;
            active = true;
            id = 10;
            id_master = 10;
            id_count = 11;
            std::cout << "Sou o servidor!" << std::endl;
        }
    }
    t0.join();
}

Controller::~Controller()
{
}

Chat *Controller::get_chat()
{
    return &this->chat;
}

bool Controller::verify_master()
{
    bool time = false;
    bool master = false;
    std::thread request([&time, &master, this](void) {
        char msg[] = "<21>";
        Multicast m(this->ip, this->port);
        m.send_message(msg);

        while (!time)
        {
            char *msg = m.receive_message();
            std::cout << "Verificando se existe o master: " << msg << std::endl;
            if ((strlen(msg) >= 5 && msg[0] == '[' && msg[3] == ']'))
            {
                if (msg[1] == '2' && msg[2] == '1')
                {
                    // std::cout << "O servidor master tem id: " << (int)msg[4] << std::endl;
                    this->id_master = (int)msg[4];
                    master = true;
                    return;
                }
            }
            free(msg);
        }
    });
    sleep(5);
    time = true;
    request.detach();
    return master;
}

unsigned int Controller::get_id()
{
    return id;
}

void Controller::set_id(unsigned int id)
{
    this->id = id;
}

unsigned int Controller::get_id_count()
{
    return id_count;
}
unsigned int Controller::get_next_id_count()
{
    return id_count++;
}

void Controller::set_id_count(unsigned int id_count)
{
    this->id_count = id_count;
}

int Controller::get_port()
{
    return port;
}

char *Controller::get_ip()
{
    return ip;
}

bool Controller::is_server()
{
    return this->server;
}

void Controller::set_server(bool server)
{
    this->server = server;
}

void Controller::receive()
{
    // Multicast m(this->ip, this->port);
    // while (true)
    // {
    std::thread t(server_data, this);
    t.join();
    // }
}

void Controller::send_data(char *data)
{
    // Multicast m(this->ip, this->port);
    // m.send_message(data);
    multicast.send_message(data);
}
