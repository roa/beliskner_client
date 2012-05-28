#ifndef BELISKNER_NEXTSCENE_HPP
#define BELISKNER_NEXTSCENE_HPP

#include "BaseScene.hpp"
#include "BaseRoot.hpp"

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

namespace Beliskner
{

class NoLogger : public CEGUI::Logger
{
    void logEvent (const CEGUI::String&, CEGUI::LoggingLevel)
    {}
    void setLogFilename(const CEGUI::String&, bool)
    {}
};

class NextScene : public BaseScene
{
private:
    BaseRoot* base;
    Ogre::SceneNode         *playerNode;

    CEGUI::OgreRenderer     *ceguiRenderer;
    CEGUI::Window* myRoot;

    bool sceneSwitch;

    void initSceneManager();
    void initCamera();
    void initGui();

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

    std::string playerName;
    int playerLife;
    int playerMana;

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
