#ifndef BELISKNER_CLIENT_BASENETWORK_HPP
#define BELISKNER_CLIENT_BASENETWORK_HPP

#define PORT "9034"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <vector>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "Message.hpp"
#include "BaseRoot.hpp"
#include "Receiver.hpp"
#include "Sender.hpp"

namespace Beliskner
{

class BaseNetwork
{

public:
    BaseNetwork();
    ~BaseNetwork();
    void startNet();
    Sender* getSender();

private:
    int sockfd, numbytes;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    bool pause;

    BaseRoot *base;

    Receiver *receiver;
    Sender   *sender;

    void *get_in_addr( struct sockaddr *sa );

    void initSender( int _sockfd );
    void initReceiver( int _sockfd );
};

}

#endif
