#include "Sender.hpp"

namespace Beliskner
{

Sender::Sender()
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

Sender::~Sender()
{

}

void *Sender::get_in_addr( struct sockaddr *sa )
{
    if ( sa->sa_family == AF_INET )
    {
        return &( ( ( struct sockaddr_in* )sa )->sin_addr );
    }
    return &( ( ( struct sockaddr_in6* )sa )->sin6_addr );
}

void Sender::sendTest()
{
    message *test = new message;
    test->status = ID_REQUEST;
    test->info[0] = 1;
    test->info[1] = 2;
    test->info[2] = 3;
    send(sockfd, ( void * ) test,sizeof(message), 0);

    test->status = POSITION_UPDATE;
    test->info[0] = 1;
    test->info[1] = 2;
    test->info[2] = 3;
    send(sockfd, ( void * ) test,sizeof(message), 0);

    test->status = MOVED;
    test->info[0] = 1;
    test->info[1] = 2;
    test->info[2] = 3;
    send(sockfd, ( void * ) test,sizeof(message), 0);

    test->status = STOPPED;
    test->info[0] = 1;
    test->info[1] = 2;
    test->info[2] = 3;
    send(sockfd, ( void * ) test,sizeof(message), 0);

    test->status = 1;
    test->info[0] = 1;
    test->info[1] = 2;
    test->info[2] = 3;
    send(sockfd, ( void * ) test,sizeof(message), 0);

    delete test;

    pause = true;
}

void Sender::startNet()
{
    boost::thread Net( boost::bind( &Sender::connectToServer, this ) );
}

void Sender::setPaused( bool newState )
{
    {
        boost::unique_lock<boost::mutex> lock( stateMutex );
        pause = newState;
    }

    stateChanged.notify_all();
}

void Sender::connectToServer()
{
    while( true )
    {
        blockWhilePaused();
        sendTest();
    }
}

void Sender::blockWhilePaused()
{
    boost::unique_lock<boost::mutex> lock( stateMutex );
    while( pause )
    {
        stateChanged.wait( lock );
    }
}

}
