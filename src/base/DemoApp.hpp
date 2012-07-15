#ifndef BELISKNER_DEMOAPP_HPP
#define BELISKNER_DEMOAPP_HPP

#include "OGRE/Ogre.h"
#include "OIS/OIS.h"

#include "BaseRoot.hpp"
#include "BaseNetwork.hpp"

namespace Beliskner
{

class DemoApp
{

private:
    BaseRoot* base;
    BaseNetwork * conn;

    void initDemoApp();
    void startNet();
public:
    DemoApp();
    ~DemoApp();

    void run();

};

}

#endif
