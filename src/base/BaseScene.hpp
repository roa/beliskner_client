#ifndef BELISKNER_BASESCENE_HPP
#define BELISKNER_BASESCENE_HPP

#include "OGRE/Ogre.h"
#include "OIS/OIS.h"

namespace Beliskner
{

class BaseScene : public OIS::KeyListener, public OIS::MouseListener
{
public:
    Ogre::SceneManager  *sceneManager;
    Ogre::Camera        *camera;

    std::string sceneName;

    virtual void initSceneManager()     = 0;
    virtual void initCamera()           = 0;

    virtual void destroySceneManager()  = 0;
    virtual void destroyCamera()        = 0;

    virtual void prepareScene()         = 0;
    virtual void exitScene()            = 0;
    virtual void createScene()          = 0;

    virtual void updateScene()          = 0;

    virtual bool keyPressed( const OIS::KeyEvent& evt )     = 0;
    virtual bool keyReleased( const OIS::KeyEvent& evt )    = 0;

    virtual bool mouseMoved( const OIS::MouseEvent& evt )   = 0;
    virtual bool mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id )  = 0;
    virtual bool mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id ) = 0;
};

}

#endif
