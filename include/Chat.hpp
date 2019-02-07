#ifndef CHAT_H
#define CHAT_H

#include <iostream>
#include <map>
#include "Message.hpp"
#include "Multicast.hpp"

class Chat
{
private:
  /* data */
  char *ip;
  int port;
  long long unsigned int operations;
  std::map<int, Message> messages;
  Multicast multicast;
  int qnt_message;
  bool server;

public:
  Chat();
  Chat(char ip[], int port);
  ~Chat();
  void add_message(Message m);
  Message *get_message(int id);
  void send_message(Message m);
  void add_operation();
  long long unsigned int get_operations();
  void set_operations(long long unsigned int operations);
};
#endif