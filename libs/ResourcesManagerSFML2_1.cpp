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

#include "ResourcesManagerSFML2_1.hpp"

sf::Texture* TextureManager::getResource(const std::string& fileName, const sf::IntRect &area)
{
    if(m_subrectTextures.find(fileName)==m_subrectTextures.end() || m_subrectTextures[fileName].find(area)==m_subrectTextures[fileName].end())
        loadFromFile(fileName, area);

    if(m_subrectTextures.find(fileName)!=m_subrectTextures.end())
        if(m_subrectTextures[fileName].find(area)!=m_subrectTextures[fileName].end())
            return m_subrectTextures[fileName][area];

    return 0;
}

// static TextureManager* getTextureManager();
// renvoie un pointeur sur une seule instance de TextureManager
TextureManager* TextureManager::getTextureManager()
{
    static TextureManager manager;
    return &manager;
}

void TextureManager::loadFromFile(const std::string& fileName)
{
    sf::Texture* tmpText = new sf::Texture;
    if(tmpText->loadFromFile(fileName))
        m_resources.insert(std::pair<std::string, sf::Texture* >(fileName, tmpText));
    else
    {
        delete tmpText;
#ifdef DEBUG
        // // std::cout << "CANT LOAD : " << fileName << std::endl;
#endif
    }
}

void TextureManager::loadFromFile(const std::string &fileName, const sf::IntRect &area)
{
    sf::Texture* tmpText = new sf::Texture;
    tmpText->loadFromFile(fileName);
    map_IntRect_ptrTexture tmpMap;
    tmpMap.insert(std::pair<sf::IntRect, sf::Texture*>(sf::IntRect(), tmpText));
    m_subrectTextures.insert(std::pair<std::string, map_IntRect_ptrTexture >(fileName, tmpMap));
}

TextureManager::TextureManager()
{}

TextureManager::~TextureManager()
{}

/***********************************************************************************************************/
/*********************************************** FontManager ***********************************************/

FontManager* FontManager::getFontManager()
{
    static FontManager manager;
    return &manager;
}

void FontManager::loadFromFile(const std::string& fileName)
{
    sf::Font* tmpFont = new sf::Font;
    if(tmpFont->loadFromFile(fileName))
        m_resources.insert(std::pair<std::string, sf::Font* >(fileName, tmpFont));
    else
    {
        delete tmpFont;
#ifdef DEBUG
        // // std::cout << "CANT LOAD : " << fileName << std::endl;
#endif
    }
}

FontManager::FontManager()
{}

FontManager::~FontManager()
{}
