#include "FrameListener.hpp"

namespace Beliskner
{

FrameListener::FrameListener( Ogre::RenderWindow *_window )
{
    OIS::ParamList parameters;
    size_t windowHandle = 0;
    std::ostringstream windowHandleString;

    _window->getCustomAttribute( "WINDOW", &windowHandle );
    windowHandleString << windowHandle;

    parameters.insert( std::make_pair( "WINDOW", windowHandleString.str() ) );

    inputManager = OIS::InputManager::createInputSystem( parameters );
    keyboard = static_cast<OIS::Keyboard*>( inputManager->createInputObject( OIS::OISKeyboard, false ) );

    inputHandler = new InputHandler( keyboard );
}

FrameListener::~FrameListener()
{
    delete inputHandler;
    inputManager->destroyInputObject( keyboard );
    OIS::InputManager::destroyInputSystem( inputManager );
}

bool FrameListener::frameStarted( const Ogre::FrameEvent &evt )
{
    inputHandler->handleKeyboard();
    return !inputHandler->getLeaveApp();
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
