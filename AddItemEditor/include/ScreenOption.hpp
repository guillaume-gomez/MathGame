#ifndef SCREENOPTION_H
#define SCREENOPTION_H

#include <fstream>
#include <vector>

#include "AniSprite.hpp"
#include "../constants.hpp"
#include "../files.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"
#include "Screen.hpp"

#include <SFGUI/SFGUI.hpp>


#define FOR_STL_REVERSE_ITERATOR(container_type, name, iteratorName) for(container_type::reverse_iterator iteratorName=name.rbegin(); iteratorName!=name.rend(); iteratorName++)
class ChoiceCharacter
{
    public:
        ChoiceCharacter(unsigned int type = 1);
        void defineCharacter();
        ~ChoiceCharacter();
    private:
        unsigned int m_type;
};


class ScreenOption : public Screen
{
    public:
        static std::string m_filenameChar;
        ScreenOption(unsigned int nbButon = 3);
        void activateSliding();
        void desactivateSliding();
        void save();
        virtual ~ScreenOption();
        int Run(sf::RenderWindow& app);
        inline std::string getFilenameChar()const {return m_filenameChar;};
        inline void setFilenameChar(std::string str){m_filenameChar = str;};

    private:
        sf::Sprite m_background;
        sfg::Box::Ptr m_box;
        std::vector<ChoiceCharacter> m_character_array;
        AniSprite currentChoice;
        std::string m_gravityType;
        sfg::Frame::Ptr m_frameCharacter;
        sfg::Frame::Ptr m_framePhysics;
        sfg::Box::Ptr m_layoutCharacter;
        sfg::Box::Ptr m_layoutPhysics;
        unsigned int m_nbButton;
        sfg::SFGUI m_sfgui;
        sfg::Window::Ptr m_window;
};
#endif // SCREENOPTION_H
