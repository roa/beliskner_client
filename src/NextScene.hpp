#ifndef BELISKNER_NEXTSCENE_HPP
#define BELISKNER_NEXTSCENE_HPP

#include "BaseScene.hpp"
#include "BaseRoot.hpp"
#include "Monster.hpp"

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

namespace Beliskner
{

class NextScene : public BaseScene
{
private:
    BaseRoot                *base;
    Ogre::Entity            *playerEnt;
    Ogre::SceneNode         *playerNode;
    Ogre::AnimationState    *aniState;
    Ogre::AnimationState    *aniStateTop;
    Ogre::AnimationState    *hitAni;

    bool attackPlayer;
    bool hitMonster;
    bool invertPlayerDir;
    bool magicPlayer;
    int  playerTurns;

    Monster                 *monster;
    Ogre::Entity            *monsterEnt;
    Ogre::SceneNode         *monsterNode;
    Ogre::AnimationState    *monsterState;
    Ogre::AnimationState    *monsterAttack;

    bool attackMonster;
    bool hitPlayer;
    bool invertMonsterDir;
    bool magicMonster;
    int  monsterTurns;

    bool playerAction;
    bool playerActionInProgress;
    bool monsterActionInProgress;

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

    CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

    bool attackButtonClicked( const CEGUI::EventArgs& );
    bool magicButtonClicked( const CEGUI::EventArgs& );

    std::string playerStatusString();

public:
    NextScene( std::string _sceneName );
    ~NextScene();

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
