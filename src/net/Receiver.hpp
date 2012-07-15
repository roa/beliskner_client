#ifndef BELISKNER_RECEIVER_HPP
#define BELISKNER_RECEIVER_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

#include "Message.hpp"

namespace Beliskner
{

class Receiver
{
private:
    int sockfd;
    void handleMessage( message msg );

public:
    Receiver( int _sockfd );
    ~Receiver();
    void recvFromServer();
};

}

#endif
