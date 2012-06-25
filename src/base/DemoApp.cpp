#include "DemoApp.hpp"

namespace Beliskner
{

DemoApp::DemoApp()
{
    base = NULL;
    conn = NULL;
    startNet();
    initDemoApp();
}

DemoApp::~DemoApp()
{
    delete conn;
}

void DemoApp::initDemoApp()
{
    new BaseRoot();
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
    conn = new Connection;
    boost::thread Net(boost::bind(&DemoApp::connectTest, this));
}

void DemoApp::connectTest()
{
    while( true )
    {
        conn->sendTest();
        sleep( 5 );
    }
}

}
