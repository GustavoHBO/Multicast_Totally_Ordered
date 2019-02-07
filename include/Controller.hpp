#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Chat.hpp"

class Controller
{
  private:
    Chat chat;
    Multicast *m;
    char *ip;
    int port;
  public:
    Controller(char ip[], int port);
    ~Controller();
    void receive();
    Chat *get_chat();
};

#endif