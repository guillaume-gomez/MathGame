#ifndef SCREENOPTION_H
#define SCREENOPTION_H

#include <fstream>

#include "../libs/Menu.hpp"
#include "../libs/Cursor.hpp"
#include "../libs/Button.hpp"
#include "../files.hpp"
#include "../constants.hpp"
#include "AniSprite.hpp"
#include "Screen.hpp"

#include "../libs/ResourcesManagerSFML2_0.hpp"

#include <vector>

#define FOR_STL_REVERSE_ITERATOR(container_type, name, iteratorName) for(container_type::reverse_iterator iteratorName=name.rbegin(); iteratorName!=name.rend(); iteratorName++)

class ScreenOption : public Screen
{
    public:
        ScreenOption(unsigned int nbButon = 3);
        virtual ~ScreenOption();
        int Run( sf::RenderWindow& app);
    private:
        Cursor *m_cursor;
        Menu m_menu;
        unsigned int m_nbButton;
        std::vector<Button*> m_listButton;
        Button* m_sliding;
        Button* m_noSliding;
        AniSprite currentChoice;
        sf::Sprite m_background;

};

#endif // SCREENOPTION_H
