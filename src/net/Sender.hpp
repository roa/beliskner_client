#ifndef BELISKNER_CLIENT_SENDER_HPP
#define BELISKNER_CLIENT_SENDER_HPP

#include <sys/types.h>
#include <sys/socket.h>

#include <boost/thread.hpp>

#include "Message.hpp"

namespace Beliskner
{

class Sender
{
private:
    int sockfd;

    bool pause;

    boost::mutex stateMutex;
    boost::condition_variable stateChanged;

    std::vector<message> messageQueue;

    void blockWhilePaused();

public:
    Sender( int _sockfd );
    ~Sender();

    void sendToServer();
    void setPaused( bool newState );
    void setMessageQueue( message newMsg );
};

}

#endif
