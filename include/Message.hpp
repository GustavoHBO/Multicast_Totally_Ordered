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
    void set_sender(char *sender);
    char *get_sender();
    void set_destination(char *destination);
    char *get_destination();
    void set_message(char *message);
    char *get_message();
    void set_date(char *date);
    char *get_date();
};

#endif