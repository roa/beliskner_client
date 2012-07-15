#include "Sender.hpp"

namespace Beliskner
{

Sender::Sender( int _sockfd ) : sockfd( _sockfd )
{

}

Sender::~Sender()
{

}

void Sender::blockWhilePaused()
{
    boost::unique_lock<boost::mutex> lock( stateMutex );
    while( pause )
    {
        stateChanged.wait( lock );
    }
}

void Sender::sendToServer()
{
    while( true )
    {
        blockWhilePaused();
        /*
            TODO: check, if simple send is enough
        */
        while( !messageQueue.empty() )
        {
            message msg = messageQueue.back();
            send( sockfd, &msg, sizeof( message ), 0 );
            messageQueue.pop_back();
        }
        pause = true;
    }
}

void Sender::setPaused( bool newState )
{
    {
        boost::unique_lock<boost::mutex> lock( stateMutex );
        pause = newState;
    }

    stateChanged.notify_all();
}

void Sender::setMessageQueue( message newMsg )
{
    messageQueue.push_back( newMsg );
}

}
