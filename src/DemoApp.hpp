#ifndef BELISKNER_DEMOAPP_HPP
#define BELISKNER_DEMOAPP_HPP

#include "OGRE/Ogre.h"
#include "OIS/OIS.h"

#include "BaseRoot.hpp"
#include "DemoScene.hpp"

namespace Beliskner
{

class DemoApp
{
private:
    BaseRoot*   base;
    DemoScene*  scene;

    void initDemoApp();

public:
    DemoApp();
    ~DemoApp();

    void run();
};

}

#endif
