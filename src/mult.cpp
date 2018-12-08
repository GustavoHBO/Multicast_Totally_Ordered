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
    static const int MAX_LEN = 1024;
    static const int MIN_PORT = 1024;
    static const int MAX_PORT = 65535;

    int sock;                   /* socket descriptor */
    char send_str[MAX_LEN];     /* string to send */
    struct sockaddr_in mc_addr; /* socket address structure */
    unsigned int send_len;      /* length of string to send */
    char *mc_addr_str;          /* multicast IP address */
    unsigned short mc_port;     /* multicast port */
    unsigned char mc_ttl;       /* time to live (hop count) */
  public:
    Multicast();
    ~Multicast();
    bool startSocketDefault();
    int createSocket();
    int setPort(int port);
    int setTTL(int time); // In seconds
    int sendSocketMessage(char *message);
};

Multicast::Multicast()
{
    this->mc_port = 65534;
    this->mc_ttl = 1;
    this->mc_addr_str = "224.0.0.1";
    this->startSocketDefault();
}

Multicast::~Multicast()
{
    close(sock);
}

bool Multicast::startSocketDefault()
{
    /* create a socket for sending to the multicast address */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        perror("The socket to send message not be created!");
        return false;
    }

    /* set the TTL (time to live/hop count) for the send */
    if ((setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL,
                    (void *)&mc_ttl, sizeof(mc_ttl))) < 0)
    {
        perror("Set the TTL time wasn't be set!");
        return false;
    }

    /* construct a multicast address structure */
    memset(&mc_addr, 0, sizeof(mc_addr));
    mc_addr.sin_family = AF_INET;
    mc_addr.sin_addr.s_addr = inet_addr(mc_addr_str);
    mc_addr.sin_port = htons(mc_port);
}

int Multicast::createSocket()
{
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
        perror("socket() failed");
        return -1;
    }
    return 0;
}

int Multicast::setPort(int port)
{
    if (port < MIN_PORT || port > MAX_PORT)
    {
        fprintf(stderr, "Invalid port number argument %d.\n", mc_port);
        fprintf(stderr, "Valid range is between %d and %d.\n", MIN_PORT, MAX_PORT);
        return -1;
    }
    this->mc_port = port;
    return 0;
}

int Multicast::setTTL(int time)
{
    if ((setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (void *)&mc_ttl, sizeof(mc_ttl))) < 0)
    {
        perror("setsockopt() failed");
        return -1;
    }
    return 0;
}

int Multicast::sendSocketMessage(char *message)
{
    printf("%d\n", strlen(message));
    if (strlen(message) > MAX_LEN)
    {
        perror("This message is very big!");
        return -1;
    }
    else
    {
        printf("Enviando\n");
        memset(send_str, 0, sizeof(send_str));
        fgets(send_str, MAX_LEN, stdin);
        //strcpy(send_str, "a");
        // this->send_str[0] = 97;
        // this->send_str[1] = 1;
        // scanf("%s", send_str);
        this->send_len = strlen(send_str);
        //send(sock, send_str, send_len, 1);
        for (int i = 0; i < 1024; i++)
        {
            printf("%d", send_str[i]);
        }
        printf("\n%d\n", send_len);
        sendto(sock, this->send_str, send_len, 0, (struct sockaddr *)&mc_addr, sizeof(mc_addr));
        // if ((sendto(sock, send_str, send_len, 0, (struct sockaddr *)&mc_addr, sizeof(mc_addr))) != send_len)
        // {
        //     perror("sendto() sent incorrect number of bytes");
        //     return -1;
        // }
    }
}

int main()
{
    struct sockaddr_in addr;
    int fd, cnt;
    struct ip_mreq mreq;
    char *message = "Hello, World!";

    /* create what looks like an ordinary UDP socket */
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        exit(1);
    }

    /* set up destination address */
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("224.0.0.1");
    addr.sin_port = htons(65534);

    /* now just sendto() our destination! */
    while (1)
    {
        if (sendto(fd, message, sizeof(message), 0, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            perror("sendto");
            exit(1);
        }
        sleep(1);
    }
    return 0;
}