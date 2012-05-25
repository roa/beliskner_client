#ifndef BELISKNER_INPUTHANDLER_HPP
#define BELISKNER_INPUTHANDLER_HPP

#include "OIS/OIS.h"

namespace Beliskner
{

class InputHandler
{
private:
    OIS::Keyboard *keyboard;
    bool leaveApp;

    void whichKeyDown();
    void setLeaveApp();


public:
    InputHandler( OIS::Keyboard *_keyboard );
    ~InputHandler();

    void handleKeyboard();
    bool getLeaveApp();
};

}

#endif
