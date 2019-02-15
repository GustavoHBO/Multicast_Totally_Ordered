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
  std::map<int, Message> messages;
  std::map<int, const char*> operations;
  Multicast multicast;
  int qnt_message;

public:
  Chat();
  Chat(char ip[], int port);
  ~Chat();
  void add_message(Message m);
  Message *get_message(int id);
  void send_message(Message m);
  void add_operation(const char*);
  std::map<int, const char*> get_operations();
  void set_operations(std::map<int, const char*> operations);
};
#endif