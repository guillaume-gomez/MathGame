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

#include "CharacterView.hpp"
#include <iostream>
#include <sstream>

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

CharacterView::CharacterView(const CharacterModel& model, float scale)
    :m_sound(CharacterView::soundBuff), m_model(model), m_left(false), m_scale(scale)
{

    // std::cout << "Main constructor of CharacterView" << std::endl;

    std::ifstream configFile(FilenameConfigFile);
    std::string tmpString;
    std::string fileName;
    float _h,_w;
    configFile >> tmpString >> tmpString;
    tmpString.clear();
    configFile >> fileName;
    configFile >> tmpString >> tmpString;
    configFile >> _w;
    configFile >> tmpString >> tmpString;
    configFile >> _h;
    configFile.close();
//	m_animation(CharacterView::characterTex,_w,_h);
    setTexture(TextureManager::getTextureManager()->getResource(fileName), _w, _h);
    m_animation.SetLoopTime(1);
    m_animation.Play();

    m_sound.setVolume(DefaultSoundVolume);
}

CharacterView::~CharacterView()
{
    m_sound.stop();
    if(!m_loadedTextureSuccess)
    {
        delete m_ArtTexture;
    }
}


CharacterView::CharacterView(const CharacterView& copy)
    :m_sound(copy.m_sound), m_model(new CharacterModel(copy.m_model.isAlive(), copy.m_model.getCoords(), 12)),
     m_left(copy.m_left), m_scale(copy.m_scale)
//share the same texture for all the instance
//m_ArtTexture(copy.m_ArtTexture)
{
    // std::cout << "Copy constructor of the class CharacterView  " << &m_model << std::endl;

    std::ifstream configFile(FilenameConfigFile);
    std::string tmpString;
    std::string fileName;
    float _h,_w;
    configFile >> tmpString >> tmpString;
    tmpString.clear();
    configFile >> fileName;
    configFile >> tmpString >> tmpString;
    configFile >> _w;
    configFile >> tmpString >> tmpString;
    configFile >> _h;
    configFile.close();
//  m_animation(CharacterView::characterTex,_w,_h);
    setTexture(TextureManager::getTextureManager()->getResource(fileName), _w, _h);
    m_animation.SetLoopTime(1);
    m_animation.Play();

    m_sound.setVolume(copy.m_sound.getVolume());
}


void CharacterView::draw( sf::RenderTarget& target)
{
    m_animation.setOrigin(m_animation.getLocalBounds().width / 2, m_animation.getLocalBounds().height);
//    m_animation.setPosition(m_model.getCoords().x*m_scale-m_animation.getLocalBounds().width/2
//							, -m_model.getCoords().y*m_scale-m_animation.getLocalBounds().height);
    m_animation.setPosition(m_model.getCoords().x * m_scale
                            , -m_model.getCoords().y * m_scale);
    m_animation.setRotation(-(m_model.getAngle() * 180) / /*M_PI*/3.14 );
    target.draw(m_animation);
}


void CharacterView::show()
{
    //setTexture(TextureManager::getTextureManager()->getResource(FilenameCharacterTex),34, 34);
    sf::Vector2f thrust = m_model.getPhysicsBox().getThrust();

#ifdef DEBUG
    //   // std::cout << "CharacterView &m_model : " << &m_model << " thrust : " << m_model.getPhysicsBox("show").getThrust().x << std::endl;
    // // std::cout << "m_model.getPhysicsBox().getThrust() : " << m_model.getPhysicsBox("xthrust").getThrust().x << std::endl;
#endif

    if(thrust.x < 0)
    {
        m_left = true;
        m_animation.Play(0,m_animation.GetFrameCount() / 2 -1);
    }
    else if(thrust.x > 0)
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
