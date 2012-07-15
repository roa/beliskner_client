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
    boost::thread BaseNetwork( boost::bind( &BaseNetwork::sendToServer, this ) );
    boost::thread receiver( boost::bind( &BaseNetwork::recvFromServer, this ) );
    recvHandler = new RecvHandler();
}

void BaseNetwork::setPaused( bool newState )
{
    {
        boost::unique_lock<boost::mutex> lock( stateMutex );
        pause = newState;
    }

    stateChanged.notify_all();
}

void BaseNetwork::setMessageQueue( message newMsg )
{
    messageQueue.push_back( newMsg );
}

void *BaseNetwork::get_in_addr( struct sockaddr *sa )
{
    if ( sa->sa_family == AF_INET )
    {
        return &( ( ( struct sockaddr_in* )sa )->sin_addr );
    }
    return &( ( ( struct sockaddr_in6* )sa )->sin6_addr );
}

void BaseNetwork::sendToServer()
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

void BaseNetwork::recvFromServer()
{
    while( true )
    {
        message msg;
        recv( sockfd, &msg, sizeof( message ), 0 );
        recvHandler->handleMessage( msg );
    }
}

void BaseNetwork::blockWhilePaused()
{
    boost::unique_lock<boost::mutex> lock( stateMutex );
    while( pause )
    {
        stateChanged.wait( lock );
    }
}

}
