#ifndef BELISKNER_RECVHANDLER_HPP
#define BELISKNER_RECVHANDLER_HPP

#include "Message.hpp"
#include <iostream>

namespace Beliskner
{

class RecvHandler
{
public:
    RecvHandler();
    ~RecvHandler();

    void handleMessage( message msg );
};

}

#endif
