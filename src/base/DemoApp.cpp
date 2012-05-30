#include "DemoApp.hpp"

namespace Beliskner
{

DemoApp::DemoApp()
{
    base            = NULL;
    initDemoApp();
}

DemoApp::~DemoApp()
{

}

void DemoApp::initDemoApp()
{
    new BaseRoot();
    base = BaseRoot::getSingletonPtr();
}

void DemoApp::run()
{
    base->sceneManager->startMainScene();
    while( base->running() )
    {
        base->renderOneFrame();
    }
}

}
