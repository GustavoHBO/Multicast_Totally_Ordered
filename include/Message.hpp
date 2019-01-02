#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>

class Message
{
  private:
    /* data */
    char *sender;
    char *destination;
    char *message;
    char *date;

  public:
    Message(/* args */);
    ~Message();
    void setSender(char *sender);
    char *getSender();
    void setDestination(char *destination);
    char *getDestination();
    void setMessage(char *message);
    char *getMessage();
    void setDate(char *date);
    char *getDate();
};

#endif