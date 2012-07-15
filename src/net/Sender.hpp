#ifndef BELISKNER_CLIENT_SENDER_HPP
#define BELISKNER_CLIENT_SENDER_HPP

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

namespace Beliskner
{

class Sender
{

public:
    Sender();
    ~Sender();
    void startNet();
    void setPaused( bool newState );
    void setMessageQueue( message newMsg );

private:
    int sockfd, numbytes;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    bool pause;

    boost::mutex stateMutex;
    boost::condition_variable stateChanged;

    BaseRoot *base;

    std::vector<message> messageQueue;

    void *get_in_addr( struct sockaddr *sa );
    void sendToServer();
    void recvFromServer();
    void blockWhilePaused();

};

}

#endif
