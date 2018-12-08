#include <sys/types.h>  /* for type definitions */
#include <sys/socket.h> /* for socket API function calls */
#include <netinet/in.h> /* for address structs */
#include <arpa/inet.h>  /* for sockaddr_in */
#include <stdio.h>      /* for printf() */
#include <stdlib.h>     /* for atoi() */
#include <string.h>     /* for strlen() */
#include <unistd.h>     /* for close() */
#include <iostream>

class Multicast
{
  private:
    /* data */
    const int MAX_LEN = 1024;
    const int MIN_PORT = 1024;
    const int MAX_PORT = 65535;
    const int MAX_BUFFER_SIZE = 1024; 
    char *ip_group;
    int port;
    struct sockaddr_in address;
    int socketNumber;
    char *data;

  public:
    Multicast(char *ip, int port);
    ~Multicast();
    int sendSocketMessage(char *message);
};

Multicast::Multicast(char *ip, int port)
{
    ip_group = ip;
    this->port = port;
    /* create what looks like an ordinary UDP socket */
    if ((socketNumber = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        exit(1);
    }

    /* set up destination address */
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip_group);
    address.sin_port = htons(port);
}

Multicast::~Multicast()
{
    close(socketNumber);
}

int Multicast::sendSocketMessage(char *msg)
{
    if (sendto(socketNumber, msg, sizeof(msg), 0, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("sendto");
        exit(1);
    }
}

int main()
{
    Multicast m("224.0.0.1", 65534);
    m.sendSocketMessage("oi");
    return 0;
}