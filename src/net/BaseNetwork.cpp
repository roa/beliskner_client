#include "BaseNetwork.hpp"

namespace Beliskner
{

BaseNetwork::BaseNetwork()
{
    pause = false;
    base = BaseRoot::getSingletonPtr();
    memset( &hints, 0, sizeof hints );
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if( ( rv = getaddrinfo( "localhost", PORT, &hints, &servinfo ) ) != 0 )
    {
        fprintf( stderr, "getaddrinfo: %s\n", gai_strerror( rv ) );
    }

    for( p = servinfo; p!= NULL; p = p->ai_next )
    {
        if( ( sockfd = socket( p->ai_family, p->ai_socktype, p->ai_protocol ) ) == -1 )
        {
            perror( "client: Socket" );
            continue;
        }
        if( connect( sockfd, p->ai_addr, p->ai_addrlen ) == -1 )
        {
            close( sockfd );
            perror( "client: connect" );
            continue;
        }
        break;
    }

    if( p == NULL )
    {
        fprintf( stderr, "client: failed to connect\n" );
    }

    inet_ntop( p->ai_family, get_in_addr( ( struct sockaddr * )p->ai_addr ), s , sizeof s );
    printf( "client: connecting to %s\n", s );

    freeaddrinfo( servinfo );

}

BaseNetwork::~BaseNetwork()
{

}

void BaseNetwork::startNet()
{
    boost::thread sender( boost::bind( &BaseNetwork::initSender, this, sockfd ) );
    boost::thread receiver( boost::bind( &BaseNetwork::initReceiver, this, sockfd ) );
}

Sender* BaseNetwork::getSender()
{
    return sender;
}

void *BaseNetwork::get_in_addr( struct sockaddr *sa )
{
    if ( sa->sa_family == AF_INET )
    {
        return &( ( ( struct sockaddr_in* )sa )->sin_addr );
    }
    return &( ( ( struct sockaddr_in6* )sa )->sin6_addr );
}

void BaseNetwork::initSender( int _sockfd )
{
    sender = new Sender( _sockfd );
    sender->sendToServer();
}

void BaseNetwork::initReceiver( int _sockfd )
{
    receiver = new Receiver( sockfd );
    receiver->recvFromServer();
}

}
