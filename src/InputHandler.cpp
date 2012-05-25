#include "InputHandler.hpp"

namespace Beliskner
{

InputHandler::InputHandler( OIS::Keyboard *_keyboard )
{
    keyboard = _keyboard;
    leaveApp = false;
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
