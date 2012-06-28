#ifndef BELISKNER_DEMOAPP_HPP
#define BELISKNER_DEMOAPP_HPP

#include "OGRE/Ogre.h"
#include "OIS/OIS.h"

#include "BaseRoot.hpp"
#include "Connection.hpp"

namespace Beliskner
{

class DemoApp
{

private:
    BaseRoot* base;
    Connection* conn;

    void initDemoApp();
    void connectTest();
    void startNet();

public:
    DemoApp();
    ~DemoApp();

    void run();

};

}

#endif
