#ifndef BELISKNER_DEMOSCENE2_HPP
#define BELISKNER_DEMOSCENE2_HPP

#include "BaseScene.hpp"
#include "BaseRoot.hpp"

namespace Beliskner
{

class DemoScene2 : public BaseScene
{

public:
    DemoScene2( std::string _sceneName );
    ~DemoScene2();

    BaseRoot* base;

    void createScene();
    void initSceneManager();
    void initCamera();
    void destroySceneManager();
    void destroyCamera();
    void enterScene();
    void exitScene();
    void initBaseRoot();
};

}

#endif
