#ifndef BELISKNER_FIGHTSCENE_HPP
#define BELISKNER_FIGHTSCENE_HPP

#include "BaseScene.hpp"
#include "BaseRoot.hpp"
#include "Monster.hpp"

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

namespace Beliskner
{

class Monster;

class FightScene : public BaseScene
{
private:
    BaseRoot                *base;
    std::vector<Monster*>   *monsterVector;
    int monsterNum;
    //Monster                 *monster;

    bool playerAction;

    CEGUI::DefaultWindow    *displayedPlayerStatus;
    CEGUI::OgreRenderer     *ceguiRenderer;
    CEGUI::Window           *myRoot;

    bool sceneSwitch;

    void initSceneManager();
    void initCamera();
    void initGui();
    void initMonster();

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

    CEGUI::MouseButton convertButton( OIS::MouseButtonID buttonID );

    bool attackButtonClicked( const CEGUI::EventArgs& );
    bool magicButtonClicked( const CEGUI::EventArgs& );

    std::string playerStatusString();

public:
    FightScene( std::string _sceneName );
    ~FightScene();

    void createScene();
    void prepareScene();
    void exitScene();
    void switchScene();

    void updateScene();
    void updateTurn();
    void updateGui();
};

}

#endif
