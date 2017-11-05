/*
 *  A 2D video game in C++ with SFML where platforms are actually Maths Curves resulting of equations you write
 *  Copyright (C) 2013,2017  Gomez Guillaume, Jarretier Adrien
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.*
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Contact us on Github : https://github.com/guillaume-gomez/MathGame
 *                      or https://github.com/AdrienJarretier
 */

#include "Game.hpp"
#include <iostream>


Game::Game(RenderWindow& _app , Difficulty _diff)
:m_typeOfCamera(TypeOfCamera::Moveable),
 m_app(_app),
 m_axis(GraphScale),
 m_textAreaFunction(6),
 m_level(1,_diff,GraphScale),
 m_gameMode(GameMode::Classic),
 m_buttonReset(FilenameButtonReset),
 m_buttonSound(FilenameSound, WidthIcon, HeightIcon),
 m_buttonBack(FilenameButtonBack),
#ifdef DEBUG
 m_frameCount(0),
 m_frameCountText("hello", *FontManager::getFontManager()->getResource("resources/fonts/garde.ttf")),
#endif
 m_gameStarted(false), m_isZoom(false), m_isSound(true), m_isBack(false),
 m_player(new Hero), m_playerDead(false)
{
    #ifdef DEBUG
//        std::cout << "game constructor" << std::endl;
    #endif // DEBUG
    loadConfigFile();
    setCenterCamera();
    sf::Texture* text = TextureManager::getTextureManager()->getResource(std::string(FilenameBGGame));
    text->setRepeated(true);
    m_spriteBG.setTexture(*text);
    m_spriteBG.setTextureRect(sf::IntRect(0, 0, WidthWorld, HeightWorld));
    m_spriteBG.setPosition(-1030, -1030);
    m_spriteBG.setColor(sf::Color(gridGameColor, gridGameColor, gridGameColor));

    int __x = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionTextAreaX*m_app.getSize().x , PositionTextAreaY*m_app.getSize().y)))).x;
    int __y = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionTextAreaX*m_app.getSize().x , PositionTextAreaY*m_app.getSize().y)))).y ;


    //doesn't work
    m_textAreaFunction.setCharacterSize(20);
    m_textAreaFunction.setPosition(0, m_app.getSize().y - m_textAreaFunction.getGlobalBounds().height - 10);

    __x = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionNBAttempX*m_app.getSize().x , PositionNBAttempY*m_app.getSize().y)))).x;
    __y = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionNBAttempX*m_app.getSize().x , PositionNBAttempY*m_app.getSize().y)))).y ;
    m_level.setnbAttempTextPosition(sf::Vector2f(__x, __y));

     __x = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionButtonResetX*m_app.getSize().x , PositionButtonResetY*m_app.getSize().y)))).x;
     __y = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionButtonResetX*m_app.getSize().x , PositionButtonResetY*m_app.getSize().y)))).y ;
    m_buttonReset.setPosition(__x, __y);

    __x = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionButtonSoundX*m_app.getSize().x , PositionButtonSoundY*m_app.getSize().y)))).x;
    __y = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionButtonSoundX*m_app.getSize().x , PositionButtonSoundY*m_app.getSize().y)))).y ;
    m_buttonSound.setPosition(__x, __y);

    __x = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionButtonBackX*m_app.getSize().x , PositionButtonBackY*m_app.getSize().y)))).x;
    __y = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionButtonBackX*m_app.getSize().x , PositionButtonBackY*m_app.getSize().y)))).y ;
    m_buttonBack.setPosition(__x, __y);




    #ifdef DEBUG
       m_frameCountText.setColor(sf::Color::Black);
    #endif
//    m_integral.build(-14.0, 14.0);

}

void Game::zoom()
{
    if( m_typeOfCamera == TypeOfCamera::Static)
    {
        float zoom = m_viewPerso.getSize().x * (1 - float(m_event.mouseWheel.delta) / 10);
        if ( zoom >= ZoomMax && zoom <= ZoomMin)
        {
            m_viewPerso.zoom(1 - float(m_event.mouseWheel.delta) / 10);
        }
    }
}

void Game::resize(float scaleX, float scaleY)
{
    resetWindow();
    m_buttonReset.scale(scaleX, scaleY);
    m_buttonBack.scale(scaleX, scaleY);
    m_buttonSound.scale(scaleX, scaleY);
    m_textAreaFunction.scale(scaleX, scaleY);
    m_level.scaleNbAttempt(scaleX, scaleY);
    #ifdef DEBUG
       m_frameCountText.scale(scaleX, scaleY);
    #endif
}

bool Game::handleInput()
{
    int oldWidth = m_app.getSize().x;
    int oldHeight = m_app.getSize().y;
    while(m_app.pollEvent(m_event))
    {
        switch(m_event.type)
        {
        case Event::Closed:
            m_app.close();
            return false;
            break;

        case sf::Event::Resized:
            resize((float)oldWidth/m_event.size.width, (float)oldHeight/m_event.size.height);
            break;

         case Event::MouseWheelMoved:
            zoom();
            m_isZoom = true;
            break;

        case Event::KeyPressed:
            if(m_event.key.code == Keyboard::F8)
            {
               resetWindow();
            }
            if(m_event.key.code == sf::Keyboard::Return)
            {
                if(getGameMode() == GameMode::Classic || getGameMode() == GameMode::NoChance)
                {
                    if(!m_gameStarted)
                    {
                       m_timer.restart();
                       m_gameStarted = true;
                    }

                    m_curves.setFunction(m_textAreaFunction.getString());
                    m_curves.build(-MaxSizeGraph, MaxSizeGraph, Step);

                    Physics::Engine::getEngine()->setFunction(m_curves.getModel());
                    m_level.decrementAttempt();
                }

            }
            if(m_event.key.code == sf::Keyboard::Escape)
            {
                m_isBack = true;
            }
            break;
        default:
            break;
        }

        if(getGameMode() == GameMode::Dynamic)
        {
            m_functionManager.handle_input(m_event);
        }

        m_textAreaFunction.handleInput(m_event, m_app);

        m_level.displaying(m_event, m_app, m_viewPerso);
        m_level.handle_inputEnnemies(m_event, m_textAreaFunction);

        if(m_gameStarted)
        {
            m_player->handle_input(m_event, m_textAreaFunction);
        }
        m_buttonReset.handle_input(m_event, m_app);
        m_buttonSound.handle_input(m_event, m_app);
        m_buttonBack.handle_input(m_event, m_app);
    }
    return true ;
}


void Game::show()
{
    m_player->show();
    m_level.showEnemies();
    m_level.displayNbAttempt();
    m_buttonSound.switchTile();
    m_textAreaFunction.blinkCaret();
//   m_functionManager.grow(0.001f);
}

void Game::draw()
{
    m_app.clear();

    m_app.setView(m_viewPerso);
    m_app.draw(m_spriteBG);

    m_axis.draw(m_app);

    if(getGameMode() == GameMode::Classic || getGameMode() == GameMode::NoChance)
    {
        m_curves.draw(m_app);
    }
    if(getGameMode() == GameMode::Dynamic)
    {
        m_functionManager.draw(m_app);
    }


    m_level.drawPoints(m_app);
    m_player->draw(m_app);

    m_app.setView(m_app.getDefaultView());
    m_level.drawUI(m_app);
    m_buttonReset.draw(m_app);
    m_buttonSound.draw(m_app);
    m_buttonBack.draw(m_app);


    m_textAreaFunction.setPosition(0, m_app.getSize().y - m_textAreaFunction.getGlobalBounds().height - 10);
    m_app.draw(m_textAreaFunction);
    //m_textFunction.draw(m_app);

    #ifdef DEBUG
        m_frameCount++;
        if(m_frameCountClock.getElapsedTime().asMilliseconds() > 250)
        {
            m_frameCountClock.restart();
            m_frameCountText.setString(std::to_string(m_frameCount*4));
            m_frameCount = 0;
        }
        m_app.draw(m_frameCountText);
    #endif
}

void Game::resetWindow()
{
    m_viewPerso.setSize(Vector2f(m_app.getSize()));
    m_viewPerso.setCenter(0, 0);

    m_level.receiveView(m_viewPerso);
    m_axis.receiveView(m_viewPerso);
    //m_functionManager.setViews(m_viewPerso);
    m_curves.receiveView(m_viewPerso);

}

void Game::cameraMoved()
{
    if(m_typeOfCamera == TypeOfCamera::Moveable)
    {
        float centerX = m_player->getView().getPosition().x,
              centerY = m_player->getView().getPosition().y;

        //Si on dépasse à gauche
        if(centerX - (m_viewPerso.getSize().x/2) < -(WidthWorld/2))
        {
           centerX = -(WidthWorld/2) + (m_viewPerso.getSize().x/2);
        }

        //Si on dépasse en haut
        if(centerY - (m_viewPerso.getSize().y/2) < -(HeightWorld/2))
        {
           centerY = -(HeightWorld/2) + (m_viewPerso.getSize().y/2);
        }

        //Si on dépasse à droite
        if(centerX + (m_viewPerso.getSize().x /2) > (WidthWorld/2))
        {
            centerX = (WidthWorld/2) - (m_viewPerso.getSize().x/2);
        }

        //si on dépasse en bas
        if(centerY + (m_viewPerso.getSize().y/2) > (HeightWorld/2))
        {
           centerY = (HeightWorld/2) - (m_viewPerso.getSize().y/2);
        }


        m_viewPerso.setCenter(centerX, centerY);
    }
}

void Game::move()
{
    if(m_gameStarted)
    {
        static float elapsedSeconds;

        elapsedSeconds = m_timer.getElapsedTime().asSeconds();

        Physics::Engine::getEngine()->update(elapsedSeconds);

        for(const EditorObject* object : m_level.getSpriteList() )
        {
            if(object->getType() == TypeObject::Enemy)
            {
                if(m_player->getModel().getPhysicsBox().testCollision(dynamic_cast<const Enemy*>(object)->getModel().getPhysicsBox())
                   )
                {
                    m_playerDead = true;
                }
            }
            if(object->getType() == TypeObject::Circle)
            {
                if(m_player->getModel().getPhysicsBox().testCollision(dynamic_cast<const GravityCircle*>(object)->getPhysicsCircle())
                   )
                {
                    m_playerDead = true;
                }
            }
        }
        if(m_player->get_Position().y<-(m_spriteBG.getTextureRect().height+m_spriteBG.getPosition().y)/GraphScale)
            m_playerDead = true;

        m_timer.restart();

       //if the mode is activated
        cameraMoved();

        m_level.receiveView(m_viewPerso);
        m_axis.receiveView(m_viewPerso);
        m_functionManager.setViews(m_viewPerso);
        m_curves.receiveView(m_viewPerso);

    }

    if(getGameMode() == GameMode::Dynamic)
    {
        if(m_functionManager.isChanged())
        {
            Physics::Engine::getEngine()->setFunction(m_functionManager.getModelIndex());
            m_functionManager.represent(Step);
            m_textAreaFunction.setString(m_functionManager.getFunction());
            m_level.decrementAttempt();
            m_timer.restart();
        }
    }

}

int Game::selectLevel(ScreenLink& stat, bool forceLoading)
{
    int changing = 0;
    try
    {
        if(!forceLoading)
        {
            changing = m_level.changeLevel(&stat);
        }
        else
        {
            changing = true;
            m_level.setLevel(stat.getCurrentLevel());
            m_level.loadFile(m_level.getLevel(), stat.getMode());
        }

        if(getGameMode() == GameMode::Dynamic)
        {
            m_gameStarted = true;
            m_level.fillLevelFunctions(m_functionManager);
            m_level.decrementAttempt();
            m_functionManager.colorize();
            Physics::Engine::getEngine()->setFunction(m_functionManager.getModelIndex());
            m_functionManager.represent(Step);
            m_textAreaFunction.setString(m_functionManager.getFunction());
            m_timer.restart();
        }
    }
    catch(std::ios_base::failure& failure)
    {
//        #ifdef DEBUG
//            std::cout << failure.what() << std::endl;
//        #endif // DEBUG
        throw;
    }
    reset();
    return changing;
}

int Game::levelOperation(ScreenLink& stat)

{
    int changing = 0;
    bool soundPlayable = false;
    m_level.levelFinished(m_player->getModel(), soundPlayable);

      //  m_player1View.m_sound.Stop();
      if(m_isSound && soundPlayable)
      {
          m_player->playSound();
      }

      if(m_buttonReset.isClicked() || m_level.getChangeLevel () || m_playerDead)
      {
        changing = selectLevel(stat);
        m_playerDead = false;
      }

      if(m_buttonBack.isClicked())
      {
          m_isBack = true;
          m_buttonBack.unclick();
      }

      return changing;
}

void Game::reset()
{
    resetWindow();

    // start the level with the first function in the list
    if(!m_functionManager.isEmpty())
    {
        m_functionManager.resetToZero();
        Physics::Engine::getEngine()->setFunction(m_functionManager.getModelIndex());
        m_textAreaFunction.setString(m_functionManager.getFunction());
    }

    if(getGameMode() == GameMode::Classic || getGameMode() == GameMode::NoChance)
    {
        m_curves.reset();
        m_gameStarted = false;
        m_textAreaFunction.setString("");
    }
    Physics::Engine::getEngine()->resetAllObjects();
    m_player->reset(m_level.getInitialPosition());
}

Game::~Game()
{    //dtor
    delete m_player;
}

void Game::manageSound()
{
    if(m_buttonSound.isClicked())
    {
         m_isSound = !m_isSound;
         m_buttonSound.unclick();
    }
}

void Game::setCenterCamera()
{

    m_viewPerso = m_app.getView();
    m_viewPerso.setCenter(0, 0);
    m_level.receiveView(m_viewPerso);
    m_axis.receiveView(m_viewPerso);
    //m_functionManager.setViews(m_viewPerso);
    m_curves.receiveView(m_viewPerso);
}

void Game::loadConfigFile()
{
  std::ifstream configFile(FilenameConfigFile);
	std::string tmpString;
	unsigned int width, height;
	float frictionCoef;
	std::string filenameTexture;
	std::string moveTypeString;
	configFile >> tmpString >> tmpString >> filenameTexture;
	configFile >> tmpString >> tmpString;
	configFile >> width;
	configFile >> tmpString >> tmpString;
	configFile >> height;
	configFile >> tmpString >> tmpString;
	configFile >> moveTypeString;
	configFile >> tmpString >> tmpString;
	configFile >> frictionCoef;

	CharacterModel::MoveType moveType=CharacterModel::NoSliding;

	if(moveTypeString=="WithSliding")
		moveType = CharacterModel::WithSliding;

	m_player->setMoveType(moveType);
	m_player->setFrictionCoefficient(frictionCoef);
	m_player->setTexture(TextureManager::getTextureManager()->getResource(filenameTexture), width, height);
	#ifdef DEBUG
        // // std::cout << "GAME CPP width : " << width << "height : " << height << std::endl;
	#endif

}

