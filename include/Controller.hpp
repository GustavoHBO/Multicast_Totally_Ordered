#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Chat.hpp"

class Controller
{
private:
  Chat chat;
  Multicast multicast;
  char *ip;
  int port, id;
  bool server;
  unsigned int id_count;

public:
  int id_master;
  Controller(char ip[], int port);
  ~Controller();
  void receive();
  Chat *get_chat();
  bool verify_master();
  bool is_server();
  void set_server(bool server);
  unsigned int get_id();
  void set_id(unsigned int id);
  unsigned int get_id_count();
  unsigned int get_next_id_count();
  void set_id_count(unsigned int id_count);
  int get_port();
  char *get_ip();
  void send_data(char *);
};

#endif