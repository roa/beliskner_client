#include "DemoApp.hpp"

namespace Beliskner
{

DemoApp::DemoApp()
{
    base    = NULL;
    scene   = NULL;
    initDemoApp();
}

DemoApp::~DemoApp()
{

}

void DemoApp::initDemoApp()
{
    new BaseRoot();
    base = BaseRoot::getSingletonPtr();
    scene = new DemoScene();
    scene->createScene();
}

void DemoApp::run()
{
    while( base->running() )
    {
        base->renderOneFrame();
    }
}

}
