#include "RecvHandler.hpp"

namespace Beliskner
{

RecvHandler::RecvHandler()
{

}

RecvHandler::~RecvHandler()
{

}

RecvHandler::handleMessage( message msg )
{
    std::cout << msg.status << std::endl;
}

}
