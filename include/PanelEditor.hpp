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

#ifndef PANELEDITOR_H
#define PANELEDITOR_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "StaticButton.hpp"
#include "../constants.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"
#include "../files.hpp"


class PanelEditor : public sf::Sprite
{
    public:
        PanelEditor();
        virtual ~PanelEditor();
        void addButton(StaticButton* button);
        StaticButton* popButton();
        StaticButton* deleteButton(unsigned int i = 0);
        StaticButton* deleteButton(StaticButton* button);
        void handle_input(sf::Event& event, sf::RenderTarget& target);
        void draw(sf::RenderTarget& app);
        void movePanel(sf::RenderTarget& target);
        void manage(int coordMouseX, sf::RenderTarget& target);
        void setAlpha (int _alpha);
        inline bool isVisible() const {return m_visible;}
    protected:
    private:
    	bool m_isAnimLeft;
    	bool m_isAnimRight;
    	std::vector<StaticButton*> m_vectButton;
    	bool m_visible;
    	sf::Clock m_timerPanel;
};

#endif // PANELEDITOR_H
