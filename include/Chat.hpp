#ifndef CHAT_H
#define CHAT_H

#include <iostream>
#include <map>
#include "Message.hpp"

class Chat
{
  private:
    /* data */
    std::map<int, Message> messages;
    int qnt_message;

  public:
    Chat(/* args */);
    ~Chat();
    void addMessage(Message m);
    Message *getMessage(int id);
};
#endif