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

#ifndef TEXTAREASFML2_0_H
#define TEXTAREASFML2_0_H

#ifdef DEBUG
#include <iostream>
#endif//DEBUG

#include <cctype>
#include <vector>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Utf.hpp>
#include <SFML/Window/Event.hpp>

#include "../files.hpp"
#include "../constants.hpp"
#include "ResourcesManagerSFML2_1.hpp"

#define FOR_STL_ITERATOR(container_type, name, iteratorName) for(container_type::iterator iteratorName=name.begin(); iteratorName!=name.end(); iteratorName++)
#define FOR_STL_REVERSE_ITERATOR(container_type, name, iteratorName) for(container_type::reverse_iterator iteratorName=name.rbegin(); iteratorName!=name.rend(); iteratorName++)

class TextAreaSFML2_0 : public sf::Drawable
{
public:
    /** Default constructor */
    TextAreaSFML2_0(unsigned int padding=0U, const sf::Color& textColor=sf::Color::Black);
    /** Default destructor */
    virtual ~TextAreaSFML2_0();

    void handleInput(const sf::Event& event, const sf::RenderTarget& target);

    void setAlphaColor(unsigned char alphaColor);
    unsigned char getAlphaColor() const;

    const sf::FloatRect getLocalBounds() const;
    const sf::FloatRect getGlobalBounds() const;

    void setPaddingTop(unsigned int value);
    void setPaddingBottom(unsigned int value);
    sf::String getString();


    void setString(std::string str);

//		/** Copy constructor
//		 *  \param other Object to copy from
//		 */
//		TextAreaSFML2_0(const TextAreaSFML2_0& other);
//		/** Assignment operator
//		 *  \param other Object to assign from
//		 *  \return A reference to this
//		 */
//		TextAreaSFML2_0& operator=(const TextAreaSFML2_0& other);
//		/** Access m_text
//		 * \return The current value of m_text
//		 */
//		const sf::Text& Gettext() const;
//		/** Access m_background
//		 * \return The current value of m_background
//		 */
//		void Setbackground(sf::Sprite val);

    bool moveCaretForward();
    bool moveCaretBackward();

    void insertCharacter(std::size_t position, sf::Uint32 utf32Char);
    void insertCharacter(sf::Uint32 utf32Char);
    void erase(std::size_t position);
    void erase();
    void eraseNext();

    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f &position);
    sf::Vector2f getPosition() const;

    void setCharacterSize(unsigned int size);

    void blinkCaret(sf::Int32 millisecondsElapsedTime = 500);
    void scale(float scaleX, float scaleY);

    void setBackgroundTexture(std::string filename);

    virtual void draw(sf::RenderTarget& target) const;
    //this method is made to change the bg size in the class InfDisplayer
    void scaleBG();

protected:
private:
    static sf::Font font;
    static sf::Texture backgroundTexture;
    static bool resourcesLoaded, fontLoaded, backgroundTextureLoaded;
    static bool loadResources(const char* fontFilename = FilenameFont, const char* textureFilename = FilenameTextAreaTex);

    void clearArtificalsEndl();
    void addArtificalsEndl();
    void checkBoundsCharacter(sf::Uint32 code);
    void checkForMaxHeightCharacter();

    std::vector<std::size_t> m_positionArtificialsEndl;
    std::size_t m_caretPosition;
    unsigned int m_paddingLeft, m_paddingRight, m_paddingTop, m_paddingBottom;
    int m_maxHeigtCharacter, m_minXCharacter;
    unsigned int m_lines;
    unsigned char m_alphaColor;
    sf::Color m_caretColor;


    sf::String m_string;
    sf::Text m_text; //!< Member variable "m_text"
    sf::Sprite m_background; //!< Member variable "m_background"
    sf::RectangleShape m_caret;
    sf::Clock m_timer;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

inline void TextAreaSFML2_0::setAlphaColor(unsigned char alphaColor)
{
    m_alphaColor = alphaColor;
    sf::Color tmpTextColor(m_text.getColor());
    tmpTextColor.a = m_alphaColor;
    m_text.setColor(tmpTextColor);
    m_background.setColor(sf::Color(255,255,255,m_alphaColor));
}

inline unsigned char TextAreaSFML2_0::getAlphaColor() const
{
    return m_alphaColor;
}

inline const sf::FloatRect TextAreaSFML2_0::getLocalBounds() const
{
    return m_background.getLocalBounds();
}

inline const sf::FloatRect TextAreaSFML2_0::getGlobalBounds() const
{
    return m_background.getGlobalBounds();
}

inline sf::String TextAreaSFML2_0::getString()
{
    clearArtificalsEndl();
    sf::String tmpString(m_string);
    addArtificalsEndl();
    return tmpString;
}

inline void TextAreaSFML2_0::setString(std::string str)
{
    m_string = str;
    m_text.setString(m_string);
    //the +1 is according to the following method "moveCaretBackward"
    m_caretPosition = m_string.getSize() + 1;

    //if the string contain the character "\n"
    for (unsigned int actualPosition = 0; actualPosition < m_string.getSize() ; actualPosition++)
    {
        if(m_string[ actualPosition ] == '\n')
        {
            m_positionArtificialsEndl.push_back(actualPosition);
            m_text.setString(m_string);
            m_lines++;
            if(actualPosition <= m_caretPosition)
                moveCaretForward();
        }
    }
    addArtificalsEndl();
    moveCaretBackward();
}

inline void TextAreaSFML2_0::setBackgroundTexture(std::string filename)
{
    m_background.setTexture(*TextureManager::getTextureManager()->getResource(filename), true);
    m_background.setScale(1, (m_maxHeigtCharacter*m_lines+m_paddingTop+m_paddingBottom)/m_background.getLocalBounds().height);
}


inline void TextAreaSFML2_0::scaleBG()
{
    m_background.setScale(1, (m_maxHeigtCharacter*m_lines+m_paddingTop+m_paddingBottom)/m_background.getLocalBounds().height);
}

//inline const sf::Text& TextAreaSFML2_0::Gettext() const
//{
//	return m_text;
//}

inline void TextAreaSFML2_0::setPaddingTop(unsigned int value)
{
    m_paddingTop = value;
}

inline void TextAreaSFML2_0::setPaddingBottom(unsigned int value)
{
    m_paddingBottom = value;
}

#endif // TEXTAREASFML2_0_H
