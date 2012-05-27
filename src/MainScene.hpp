#ifndef BELISKNER_MAINSCENE_HPP
#define BELISKNER_MAINSCENE_HPP

#include "BaseScene.hpp"
#include "BaseRoot.hpp"

namespace Beliskner
{

class MainScene : public BaseScene
{
private:
    BaseRoot* base;
    Ogre::SceneNode         *playerNode;

    Ogre::Entity            *playerEnt;
    Ogre::AnimationState    *aniState;
    Ogre::AnimationState    *aniStateTop;

    Ogre::Vector3           cameraPosition;
    Ogre::Vector3           playerPosition;

    bool playerWalked;
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
    MainScene( std::string _sceneName );
    ~MainScene();

    void createScene();
    void prepareScene();
    void exitScene();
    void switchScene();

    void updateScene();
};

}

#endif
