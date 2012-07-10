#ifndef BELISKNER_DEMOAPP_HPP
#define BELISKNER_DEMOAPP_HPP

#include "OGRE/Ogre.h"
#include "OIS/OIS.h"

#include "BaseRoot.hpp"
#include "Sender.hpp"

namespace Beliskner
{

class DemoApp
{

private:
    BaseRoot* base;
    Sender * conn;

    void initDemoApp();
    void startNet();
public:
    DemoApp();
    ~DemoApp();

    void run();

};

}

#endif
