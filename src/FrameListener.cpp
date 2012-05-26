#include "FrameListener.hpp"

namespace Beliskner
{

FrameListener::FrameListener( Ogre::RenderWindow *_window )
{
    base = BaseRoot::getSingletonPtr();

    OIS::ParamList parameters;
    size_t windowHandle = 0;
    std::ostringstream windowHandleString;

    _window->getCustomAttribute( "WINDOW", &windowHandle );
    windowHandleString << windowHandle;

    parameters.insert( std::make_pair( "WINDOW", windowHandleString.str() ) );

    inputManager = OIS::InputManager::createInputSystem( parameters );
    keyboard = static_cast<OIS::Keyboard*>( inputManager->createInputObject( OIS::OISKeyboard, false ) );
    mouse    = static_cast<OIS::Mouse*>( inputManager->createInputObject( OIS::OISMouse, false ) );

    leaveApp = false;
}

FrameListener::~FrameListener()
{
    inputManager->destroyInputObject( keyboard );
    inputManager->destroyInputObject( mouse );
    OIS::InputManager::destroyInputSystem( inputManager );
}

bool FrameListener::frameStarted( const Ogre::FrameEvent &evt )
{
    base->sceneManager->currentScene->updateScene();
    base->timer->reset();
    return !leaveApp;
}

bool FrameListener::frameEnded( const Ogre::FrameEvent &evt )
{
    return true;
}

bool FrameListener::frameRenderingQueued( const Ogre::FrameEvent &evt )
{
    return true;
}

}
