#include "Game.hpp"
#include <iostream>

//TODO m_playerModel has to change
Game::Game( RenderWindow& _app , Difficulty _diff)
:m_app(_app),m_axis( GraphScale ),m_graphView(m_graphModel,Thickness, GraphScale),m_player1Model(true, sf::Vector2f(0.0f,0.0f), 12),m_player1View(m_player1Model, GraphScale)
,m_textAreaFunction(6),m_level(1,_diff,GraphScale),m_buttonReset(FilenameButtonReset),m_buttonSound(FilenameSound,WidthIcon,HeightIcon),m_buttonBack(FilenameButtonBack),
 m_modelIntegral("x-4"),m_viewIntegral(m_modelIntegral, GraphScale),
 m_gameStarted(false),m_isZoom(false),m_isSound(true),m_isBack(false)
{
   loadConfigFile();

   setCenterCamera();


   m_viewIntegral.representLine();

	sf::Texture* text = TextureManager::getTextureManager()->getResource(std::string(FilenameBGGame));
	text->setRepeated(true);
	m_spriteBG.setTexture(*text);
	m_spriteBG.setTextureRect(sf::IntRect(0,0,2048,2048));
	m_spriteBG.setPosition(-1030,-1030);
    m_spriteBG.setColor(sf::Color(gridGameColor,gridGameColor,gridGameColor));

	m_player1Model.setSize(m_player1View.getRectLocal().width, m_player1View.getRectLocal().height);

    int __x = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionTextAreaX*m_app.getSize().x , PositionTextAreaY*m_app.getSize().y )))).x;
    int __y = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionTextAreaX*m_app.getSize().x , PositionTextAreaY*m_app.getSize().y )))).y ;
    //won't work
    m_textAreaFunction.setCharacterSize(20);

     __x = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionNBAttempX*m_app.getSize().x , PositionNBAttempY*m_app.getSize().y )))).x;
     __y = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionNBAttempX*m_app.getSize().x , PositionNBAttempY*m_app.getSize().y )))).y ;
    m_level.setnbAttempTextPosition(sf::Vector2f(__x,__y));

     __x = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionButtonResetX*m_app.getSize().x , PositionButtonResetY*m_app.getSize().y )))).x;
     __y = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionButtonResetX*m_app.getSize().x , PositionButtonResetY*m_app.getSize().y )))).y ;
    m_buttonReset.setPosition(__x,__y );

    __x = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionButtonSoundX*m_app.getSize().x , PositionButtonSoundY*m_app.getSize().y )))).x;
    __y = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionButtonSoundX*m_app.getSize().x , PositionButtonSoundY*m_app.getSize().y )))).y ;
    m_buttonSound.setPosition(__x,__y );

    __x = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionButtonBackX*m_app.getSize().x , PositionButtonBackY*m_app.getSize().y )))).x;
    __y = (Vector2f(m_app.mapPixelToCoords(Vector2i(PositionButtonBackX*m_app.getSize().x , PositionButtonBackY*m_app.getSize().y )))).y ;
    m_buttonBack.setPosition(__x,__y );


}

void Game::zoom()
{
    float zoom = m_viewPerso.getSize().x * (1-float(m_event.mouseWheel.delta)/10);
    if ( zoom >= ZoomMax && zoom <= ZoomMin)
    {
        m_viewPerso.zoom(1-float(m_event.mouseWheel.delta)/10);
    }
}

bool  Game::handleInput()
{
    while(m_app.pollEvent(m_event))
            {
                switch(m_event.type)
                {
                case Event::Closed:
                    m_app.close();
                    return false;
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
                        if(!m_gameStarted)
                        {
                            m_player1Model.resetTimer();
                            m_gameStarted = true;
                        }
						m_graphModel.setFunction(m_textAreaFunction.getString());
						m_graphModel.getRepresentativeCurve(-MaxSizeGraph,MaxSizeGraph,Step);
						m_level.decrementAttempt();
						//float tmpY;
						//if(tt.isDefined(player1Model.getCoords().x, &tmpY))
						//{
							//player1Model.setCoordY(tmpY);
						//}

						//player1Model.setCoordY(-(tt.getFunctionValue(0)*GraphsCale));
                    }
                    if(m_event.key.code == sf::Keyboard::Escape)
                    {
                        m_isBack = true;
                    }
                    break;
                default:
                    break;
                }

            //    m_textFunction.handle_input(m_event, m_graphView);
                m_textAreaFunction.handleInput(m_event,m_app);

                m_level.displaying(m_event,m_app,m_viewPerso);

              //  m_textAreaFunction.resize();


				m_player1Model.handle_input(m_event, m_textAreaFunction);
                m_buttonReset.handle_input(m_event,m_app);
                m_buttonSound.handle_input(m_event,m_app);
                m_buttonBack.handle_input(m_event,m_app);
            }
    return true ;
}


void Game::show()
{
    m_player1View.show();
    m_level.displayNbAttempt();
    m_buttonSound.switchTile();
	m_textAreaFunction.blinkCaret();
}

void Game::draw()
{
    m_app.clear();

    m_app.setView(m_viewPerso);
    m_app.draw(m_spriteBG);

    m_axis.draw(m_app);
    m_viewIntegral.drawLine(m_app);
    m_graphView.draw(m_app);
    m_level.drawPoints(m_app);
    m_player1View.draw(m_app);


    m_app.setView(m_app.getDefaultView());
    m_level.drawUI(m_app);
    m_buttonReset.draw(m_app);
    m_buttonSound.draw(m_app);
    m_buttonBack.draw(m_app);
    m_textAreaFunction.setPosition(0,m_app.getSize().y-m_textAreaFunction.getGlobalBounds().height-10);
	m_app.draw(m_textAreaFunction);
    //m_textFunction.draw(m_app);
}

void Game::resetWindow()
{
    m_viewPerso.setSize(Vector2f(m_app.getSize()));
    m_viewPerso.setCenter(0, 0);
}

void Game::move()
{
    if(m_gameStarted)
    {
        m_player1Model.move(m_graphModel);
        //
        //to following the character
        //
        //m_viewPerso.setCenter(m_player1View.getCoords());
       // m_app.setView(m_viewPerso);
    }

    if ( m_graphModel.getChanged())
    {
        m_graphView.represent(Step);
        m_graphModel.setChanged(false);
    }
}

void Game::selectLevel(ScreenLink& stat)
{
    reset();
    m_level.setDiff(stat.getDiff());
    m_level.loadFile(stat.getCurrentLevel(), stat.getMode());
}

int Game::levelOperation( ScreenLink& stat)
{
    int changing = 0;
    bool soundPlayable = false;
   // std::cout << m_player1View.getRectLocal(). << std::endl;
//    m_player1Model.setSize();
      m_level.levelFinished(m_player1Model, soundPlayable);

      //  m_player1View.m_sound.Stop();
      if ( m_isSound && soundPlayable)
      {
          m_player1View.m_sound.play();
      }

      if ( m_buttonReset.isClicked() || m_level.getChangeLevel ())
      {
        reset();
        changing = m_level.changeLevel( &stat);
      }

      if ( m_buttonBack.isClicked())
      {
          m_isBack = true;
          m_buttonBack.unclick();
      }

      return changing;
}

void Game::reset()
{
         m_player1Model.setCoords(sf::Vector2f(0.0f,0.0f));
         m_player1Model.setAngle(0.0f);
         m_player1Model.resetVelocity();
         m_graphModel.setChanged(true);
         m_graphModel.clearFunction();
         m_gameStarted = false;
}

Game::~Game()
{    //dtor
}

void Game::manageSound()
{
    if ( m_buttonSound.isClicked())
    {
         m_isSound = !m_isSound;
         m_buttonSound.unclick();
    }
}

void Game::setCenterCamera()
{
   m_viewPerso = m_app.getView();
   m_viewPerso.setCenter(0,0);
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

	m_player1Model.setMoveType(moveType);
	m_player1Model.setFrictionCoefficient(frictionCoef);
	m_player1View.setTexture(TextureManager::getTextureManager()->getResource(filenameTexture),width,height);
}

