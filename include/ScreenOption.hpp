#ifndef SCREENOPTION_H
#define SCREENOPTION_H

#include <fstream>
#include <SFGUI/SFGUI.hpp>

#include "../constants.hpp"
#include "../files.hpp"
#include "AniSprite.hpp"
#include "Screen.hpp"

#include "../libs/ResourcesManagerSFML2_1.hpp"

#include <vector>

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
        ScreenOption(unsigned int nbButon = 3);
        void activateSliding();
        void desactivateSliding();
        void save();
        virtual ~ScreenOption();
        int Run( sf::RenderWindow& app);
        inline std::string getFilenameChar()const { return m_filenameChar;};
        inline void setFilenameChar(std::string str){ m_filenameChar = str;};
    private:
        unsigned int m_nbButton;
        AniSprite currentChoice;
        sf::Sprite m_background;

        std::string m_gravityType;
        std::string m_filenameChar;

        sfg::Window::Ptr m_window;
        sfg::Box::Ptr m_box;
        sfg::Box::Ptr m_layoutPhysics;
        sfg::Box::Ptr m_layoutCharacter;
        sfg::Frame::Ptr m_framePhysics;
        sfg::Frame::Ptr m_frameCharacter;

        std::vector<ChoiceCharacter> m_character_array;

};


#endif // SCREENOPTION_H
