#include "Chat.hpp"

Chat::Chat(/* args */)
{
    qnt_message = 0;
}

Chat::~Chat()
{
}

void Chat::addMessage(Message m)
{
    messages[qnt_message++] = m;
}

Message *Chat::getMessage(int i)
{
    if (messages.find(i) == messages.end())
    {
        return NULL;
    }
    return &messages.find(i)->second;
}