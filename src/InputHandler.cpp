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
    if( keyboard->isKeyDown( OIS::KC_S ) )
    {
        base->sceneManager->switchToScene( "nextScene" );
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
