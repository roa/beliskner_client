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

private:
    int sockfd, numbytes;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    enum statuscodes
    {
        ID_REQUEST      = 60000,
        POSITION_UPDATE = 60001,
        ID_UPDATE       = 60002,
        ID_ANSwER       = 60003,
        MOVED           = 60004,
        STOPPED         = 60005
    };

    struct message
    {
        int status;
        int info[3];
    };

    void *get_in_addr(struct sockaddr *sa);

};

}

#endif
