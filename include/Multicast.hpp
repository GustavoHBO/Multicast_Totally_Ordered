#ifndef MULTICAST_H
#define MULTICAST_H

#include <sys/types.h>  /* for type definitions */
#include <sys/socket.h> /* for socket API function calls */
#include <netinet/in.h> /* for address structs */
#include <arpa/inet.h>  /* for sockaddr_in */
#include <stdio.h>      /* for printf() */
#include <stdlib.h>     /* for atoi() */
#include <string.h>     /* for strlen() */

#include <unistd.h> /* for close() */

class Multicast
{
private:
  /* data */
  static const int MIN_PORT = 1024;
  static const int MAX_PORT = 65535;
  static const int MAX_BUFFER_SIZE = 256;
  char *ip;
  int port, addrlen, nbytes;
  struct sockaddr_in address;
  struct ip_mreq mreq;
  int socketNumber;
  char buffer_data[MAX_BUFFER_SIZE];

public:
  Multicast();
  Multicast(char *ip, int port);
  ~Multicast();
  int send_message(char *message);
  char *receive_message();
};
#endif