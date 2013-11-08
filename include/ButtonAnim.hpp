#ifndef BUTTONANIM_H
#define BUTTONANIM_H

#ifdef DEBUG
	#include <iostream>
#endif // DEBUG
#include "AniSprite.hpp"
#include "ButtonPerso.hpp"

class ButtonAnim : public ButtonPerso
{
    public:
        ButtonAnim(const char* _filename = "", int _widthFrame=0,int _heigtFrame=0);
        virtual ~ButtonAnim();
        void switchTile();
      //  void draw(sf::RenderTarget& target);
        void handle_input(sf::Event& event,sf::RenderTarget& target);
        void Launch();
    private:
        sf::Texture m_texture;
        AniSprite m_spriteList;
        //to launch animation for instance;
        bool m_changing;

};



#endif // BUTTONANIM_H
