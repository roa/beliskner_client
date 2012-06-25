#ifndef BELISKNER_CLIENT_CONNECTION_HPP
#define BELISKNER_CLIENT_CONNECTION_HPP

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT "9034"

namespace Beliskner
{

class Connection
{
public:
    Connection();
    ~Connection();
    void sendTest();
    void *get_in_addr(struct sockaddr *sa);
private:
    int sockfd, numbytes;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
};

}

#endif
