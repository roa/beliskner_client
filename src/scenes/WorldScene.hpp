#ifndef BELISKNER_WORLDSCENE_HPP
#define BELISKNER_WORLDSCENE_HPP

#include "BaseScene.hpp"
#include "BaseRoot.hpp"

namespace Beliskner
{
class BaseRoot;

class WorldScene : public BaseScene
{
private:
    BaseRoot*       base;

    Ogre::Vector3   cameraPosition;
    int posChange;
    int steps;

    bool sceneSwitch;

    void initSceneManager();
    void initCamera();

    void destroySceneManager();
    void destroyCamera();

    void updateKeyboard();
    void updateMouse();
    void updateAnimations();

    bool keyPressed( const OIS::KeyEvent& evt );
    bool keyReleased( const OIS::KeyEvent& evt );

    bool mouseMoved( const OIS::MouseEvent& evt );
    bool mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id );

public:
    WorldScene( std::string _sceneName );
    ~WorldScene();

    void createScene();
    void prepareScene();
    void exitScene();
    void switchScene( std::string sceneName );
    void updateSteps();
    void updateScene();
};

}

#endif
