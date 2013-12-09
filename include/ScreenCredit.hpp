#ifndef SCREENCREDIT_H
#define SCREENCREDIT_H

#include "Screen.hpp"
#include "SFML/Graphics.hpp"
#include "../files.hpp"
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
        unsigned int picture;
        float alpha;
        bool m_hangStart;
        bool m_won;
        bool m_enterText;

        sf::Sprite m_bg;
        sf::Clock m_clock;
        sf::Clock m_clockAlpha;
        sf::Font  m_font;
        sf::Texture m_hanged;
        sf::Sprite m_hangGui;
        std::vector<sf::String> m_stringList;
        std::vector<sf::Text> m_textList;
        sf::Texture m_textUnderline;
        sf::Sprite m_underline;
        sf::String m_word;
        sf::Text m_wordText;
};

#endif // SCREENCREDIT_H
