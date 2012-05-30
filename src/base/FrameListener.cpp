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
    keyboard = static_cast<OIS::Keyboard*>( inputManager->createInputObject( OIS::OISKeyboard, true ) );
    mouse    = static_cast<OIS::Mouse*>( inputManager->createInputObject( OIS::OISMouse, true ) );

    keyboard->setEventCallback( this );
    mouse->setEventCallback( this );

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

bool FrameListener::keyPressed( const OIS::KeyEvent& evt )
{
    base->sceneManager->currentScene->keyPressed( evt );
    return true;
}

bool FrameListener::keyReleased( const OIS::KeyEvent& evt )
{
    base->sceneManager->currentScene->keyReleased( evt );
    return true;
}

bool FrameListener::mouseMoved( const OIS::MouseEvent& evt )
{
    base->sceneManager->currentScene->mouseMoved( evt );
    return true;
}

bool FrameListener::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
    base->sceneManager->currentScene->mousePressed( evt, id );
    return true;
}

bool FrameListener::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
    base->sceneManager->currentScene->mouseReleased( evt, id );
    return true;
}

}
