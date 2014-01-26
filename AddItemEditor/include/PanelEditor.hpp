#ifndef PANELEDITOR_H
#define PANELEDITOR_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "ButtonPerso.hpp" 
#include "../constants.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"
#include "../files.hpp"


class PanelEditor : public sf::Sprite
{
    public:
        PanelEditor();
        virtual ~PanelEditor();
        void addButton(ButtonPerso* button);
        ButtonPerso* popButton();
        ButtonPerso* deleteButton(unsigned int i = 0);
        ButtonPerso* deleteButton(ButtonPerso* button);
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
    	std::vector<ButtonPerso*> m_vectButton;
    	bool m_visible;
    	sf::Clock m_timerPanel;
};

#endif // PANELEDITOR_H
