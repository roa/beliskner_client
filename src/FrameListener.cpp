#include "FrameListener.hpp"

namespace Beliskner
{

FrameListener::FrameListener()
{

}

FrameListener::~FrameListener()
{

}

bool FrameListener::frameStarted( const Ogre::FrameEvent &evt )
{
    return true;
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
