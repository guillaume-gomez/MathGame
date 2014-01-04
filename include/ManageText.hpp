#ifndef ManageText_H
#define ManageText_H

#ifdef DEBUG
    #include <iostream>
#endif

#include <SFML/Graphics.hpp>
#include "GraphView.hpp"
#include "../files.hpp"
#include "../constants.hpp"

class ManageText
{
    public:
         sf::Text m_text;

        ManageText();
        virtual ~ManageText();
        inline int getSizeFont()const{return  m_sizeFont;};
        inline void setSizeFont( int _size){ m_sizeFont = _size;};
        inline sf::Font getFont() const {return m_font;};
        inline void getSizeFont( sf::Font _f){m_font = _f;};
        inline sf::String getString() const {return m_string;};
        inline void setString ( sf::String _str){m_string = _str;};
        inline void setFont ( int val){m_sizeFont = val ;};
        inline void setPosition ( sf::Vector2f pos){m_text.setPosition(pos);};
        inline void setAlpha ( int _a){ m_text.setColor(sf::Color(0, 0, 0, _a));};
        inline void setColor ( sf::Color col){m_text.setColor(col);};
        inline bool isJumpable() const {return m_jumpable;};
        inline bool isTyping() const {return m_isTyping;};
        inline void setJumpable(bool  _b){m_jumpable = _b;};
        inline void setToResize( int _i){m_toResize = _i;};
        inline int getToResize() const {return m_toResize;};
        void handle_input(const sf::Event &event, GraphView& view);
        //void displayingMode( TextArea& textarea);
        void draw(sf::RenderTarget& App);
       // void jump( TextArea& textarea);

		bool m_changed;
        friend std::ostream& operator<<( std::ostream &flux, const ManageText&  texte );
    private:
        int m_sizeFont;
        bool m_isTyping;
        bool m_jumpable;
        int m_toResize;

        sf::Font m_font;
        sf::String m_string;
};

#endif // ManageText_H
