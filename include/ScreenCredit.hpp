#ifndef SCREENCREDIT_H
#define SCREENCREDIT_H

#include "Screen.hpp"
#include "SFML/Graphics.hpp"
#include "../constants.hpp"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "../libs/ResourcesManagerSFML2_1.hpp"



class ScreenCredit : public Screen
{
    public:
        ScreenCredit();
        virtual ~ScreenCredit();
        int Run (sf::RenderWindow &App);
        void hanged();
        void handle_input(sf::Event& event);

    private:
        float alpha;
        sf::Sprite m_bg;
        sf::Clock m_clock;
        sf::Clock m_clockAlpha;
        bool m_enterText;
        sf::Font  m_font;
        sf::Texture m_hanged;
        bool m_hangStart;
        sf::Sprite m_hangGui;
        unsigned int picture;
        std::vector<sf::String> m_stringList;
        std::vector<sf::Text> m_textList;
        sf::Texture m_textUnderline;
        sf::Sprite m_underline;
        sf::String m_word;
        bool m_won;
        sf::Text m_wordText;
};

#endif // SCREENCREDIT_H
