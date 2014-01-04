#include "CharacterView.hpp"
#include <iostream>


//sf::Texture CharacterView::characterTex;
//
//bool CharacterView::characterTexLoaded = loadCharacterTex();
//
//bool CharacterView::loadCharacterTex()
//{
//	std::ifstream configFile(FilenameConfigFile);
//	std::string tmpString;
//	configFile >> tmpString >> tmpString;
//	tmpString.clear();
//	configFile >> tmpString;
//
//    return characterTex.loadFromFile(tmpString);
//}

sf::SoundBuffer CharacterView::soundBuff;

bool CharacterView::soundBufferLoaded = loadSoundBuffer(FilenameSoundBuffer);

bool CharacterView::loadSoundBuffer(const char* filename )
{
    return soundBuff.loadFromFile(filename);
}

CharacterView::CharacterView(const CharacterModel& model, float scale, int _w, int _h)
:m_sound(CharacterView::soundBuff), m_model(model), m_left(false), m_scale(scale)
{
	std::ifstream configFile(FilenameConfigFile);
	std::string tmpString;
	configFile >> tmpString >> tmpString;
	tmpString.clear();
	configFile >> tmpString;

//	m_animation(CharacterView::characterTex,_w,_h);

    setTexture(TextureManager::getTextureManager()->getResource(tmpString), _w, _h);

	m_animation.SetLoopTime(1);
	m_animation.Play();
}

CharacterView::~CharacterView()
{
    m_sound.stop();
    if(!m_loadedTextureSuccess)
    {
        delete m_ArtTexture;
    }
}

void CharacterView::draw( sf::RenderTarget& target)
{
    m_animation.setOrigin(m_animation.getLocalBounds().width / 2, m_animation.getLocalBounds().height);
//    m_animation.setPosition(m_model.getCoords().x*m_scale-m_animation.getLocalBounds().width/2
//							, -m_model.getCoords().y*m_scale-m_animation.getLocalBounds().height);
    m_animation.setPosition(m_model.getCoords().x * m_scale
                            , -m_model.getCoords().y * m_scale);

    m_animation.setRotation(-(m_model.getAngle() * 180) / M_PI );
	target.draw(m_animation);
}


void CharacterView::show()
{
    sf::Vector2f velocity = m_model.getVelocity();

    if(velocity.x < 0)
    {
        m_left = true;
        m_animation.Play(0,m_animation.GetFrameCount() / 2 -1);
    }
    else if(velocity.x > 0)
    {
        m_animation.Play(m_animation.GetFrameCount() / 2, m_animation.GetFrameCount() -1);
        m_left = false;
    }
    else
    {
        if (m_left)
        {
            m_animation.Stop(0);
        }
        else
        {
            m_animation.Stop(m_animation.GetFrameCount() / 2);
        }
    }
     m_animation.Update();
}
