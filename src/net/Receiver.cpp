#include "Receiver.hpp"

namespace Beliskner
{

Receiver::Receiver( int _sockfd) : sockfd( _sockfd )
{

}

Receiver::~Receiver()
{

}

void Receiver::handleMessage( message msg )
{
    switch( msg.status )
    {
        case POSITION_UPDATE:
        {
            std::cout << "Position Update" << std::endl;
            break;
        }
        case ID_UPDATE:
        {
            std::cout << "ID Update" << std::endl;
            break;
        }
        case ID_ANSWER:
        {
            std::cout << "ID Answer" << std::endl;
            break;
        }
        case MOVED:
        {
            std::cout << "MOVED" << std::endl;
            break;
        }
        case STOPPED:
        {
            std::cout << "Stopped" << std::endl;
            break;
        }
        default:
        {
            std::cout << "something went wrong" << std::endl;
        }
    }
}

void Receiver::recvFromServer()
{
    while( true )
    {
        message msg;
        recv( sockfd, &msg, sizeof( message ), 0 );
        handleMessage( msg );
    }
}

}
