#include "InputHandler.hpp"

namespace Beliskner
{

InputHandler::InputHandler( OIS::Keyboard *_keyboard )
{
    keyboard = _keyboard;
    leaveApp = false;
    base = BaseRoot::getSingletonPtr();
}

InputHandler::~InputHandler()
{

}

void InputHandler::whichKeyDown()
{
    if( keyboard->isKeyDown( OIS::KC_ESCAPE ) )
    {
        setLeaveApp();
    }
    if( keyboard->isKeyDown( OIS::KC_S) )
    {
        base->sceneManager->switchScene = true;
        base->sceneManager->switchToScene( "nextScene" );
    }
    if( keyboard->isKeyDown( OIS::KC_A) )
    {
        base->sceneManager->switchScene = true;
        base->sceneManager->switchToScene( "mainScene" );
    }
}

void InputHandler::handleKeyboard()
{
    keyboard->capture();
    whichKeyDown();
}

void InputHandler::setLeaveApp()
{
    leaveApp = true;
}

bool InputHandler::getLeaveApp()
{
    return leaveApp;
}

}
