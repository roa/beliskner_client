#ifndef BELISKNER_DEMOSCENE_HPP
#define BELISKNER_DEMOSCENE_HPP

#include "BaseScene.hpp"
#include "BaseRoot.hpp"

namespace Beliskner
{

class DemoScene : public BaseScene
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

public:
    DemoScene( std::string _sceneName );
    ~DemoScene();

    void createScene();
    void prepareScene();
    void exitScene();
    void switchScene();

    void updateScene();
};

}

#endif
