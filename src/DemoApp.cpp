#include "DemoApp.hpp"

namespace Beliskner
{

DemoApp::DemoApp()
{
    base            = NULL;
    sceneManager    = NULL;
    initDemoApp();
}

DemoApp::~DemoApp()
{

}

void DemoApp::initDemoApp()
{
    sceneManager = new SceneManager();
    base = BaseRoot::getSingletonPtr();
}

void DemoApp::run()
{
    sceneManager->startMainScene();
    while( base->running() )
    {
        base->renderOneFrame();
    }
}

}
