#ifndef BELISKNER_DEMOSCENE_HPP
#define BELISKNER_DEMOSCENE_HPP

#include "BaseScene.hpp"
#include "BaseRoot.hpp"

namespace Beliskner
{

class DemoScene : public BaseScene
{

public:
    DemoScene( std::string _sceneName );
    ~DemoScene();

    BaseRoot* base;

    void createScene();
    void initSceneManager();
    void initCamera();
    void destroySceneManager();
    void destroyCamera();
    void exitScene();
    void enterScene();
    void initBaseRoot();
    void handleInput();
};

}

#endif
