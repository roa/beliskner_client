#ifndef BELISKNER_DEMOSCENE2_HPP
#define BELISKNER_DEMOSCENE2_HPP

#include "BaseScene.hpp"
#include "BaseRoot.hpp"

namespace Beliskner
{

class DemoScene2 : public BaseScene
{
private:
    BaseRoot* base;
    Ogre::SceneNode         *playerNode;

    bool sceneSwitch;

    void initSceneManager();
    void initCamera();

    void destroySceneManager();
    void destroyCamera();

    void updateKeyboard();
    void updateMouse();
    void updateAnimations();

public:
    DemoScene2( std::string _sceneName );
    ~DemoScene2();

    void createScene();
    void prepareScene();
    void exitScene();
    void switchScene();

    void updateScene();
};

}

#endif
