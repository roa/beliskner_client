#include "DemoApp.hpp"

namespace Beliskner
{

DemoApp::DemoApp()
{
    base = NULL;
    conn = NULL;
    initDemoApp();
    startNet();
}

DemoApp::~DemoApp()
{
    delete conn;
}

void DemoApp::initDemoApp()
{
    conn = new BaseNetwork;
    new BaseRoot( conn );
    base = BaseRoot::getSingletonPtr();
}

void DemoApp::run()
{
    base->sceneManager->startWorldScene();
    while( base->running() )
    {
        base->renderOneFrame();
    }
}


void DemoApp::startNet()
{
    conn->startNet();
}

}
