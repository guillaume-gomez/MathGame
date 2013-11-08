#ifndef SCREENFINISH_H
#define SCREENFINISH_H

#include "Screen.hpp"
#include "SFML/Graphics.hpp"
#include "../files.hpp"

#include "../libs/ResourcesManagerSFML2_0.hpp"

class ScreenFinish : public Screen
{
    public:
        ScreenFinish();
        virtual ~ScreenFinish();
        int Run(sf::RenderWindow & App);
    protected:
    private:
        sf::Clock m_clock;
        sf::Sprite m_bg;

};

#endif // SCREENFINISH_H
