#ifndef BELISKNER_NEXTSCENE_HPP
#define BELISKNER_NEXTSCENE_HPP

#include "BaseScene.hpp"
#include "BaseRoot.hpp"

namespace Beliskner
{

class NextScene : public BaseScene
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
    NextScene( std::string _sceneName );
    ~NextScene();

    void createScene();
    void prepareScene();
    void exitScene();
    void switchScene();

    void updateScene();
};

}

#endif
