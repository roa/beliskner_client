#ifndef BELISKNER_DEMOSCENE_HPP
#define BELISKNER_DEMOSCENE_HPP

#include "BaseScene.hpp"

namespace Beliskner
{

class DemoScene : public BaseScene
{

public:
    DemoScene( std::string _sceneName );
    ~DemoScene();

    void createScene();
    void createScene2();
};

}

#endif
