#include "PanelEditor.hpp"

PanelEditor::PanelEditor()
:m_isAnimLeft(false), m_isAnimRight(false),m_visible(true)
{
	sf::Texture * texture = 0;
    texture = TextureManager::getTextureManager()->getResource(std::string(FilenameButtonPanel));

    if(texture)
    {
        this->setTexture(*texture);
    }
    else
    {
        std::cout << "Warning : in ButtonPerso, Constructor didn't find a file texture " << FilenameButtonPanel << std::endl;
    }

}

PanelEditor::~PanelEditor()
{
    for (unsigned int i = 0; i < m_vectButton.size(); i++)
    {
        // TODO µµµµµµµ
    	//ButtonPerso * temp = m_vectButton.pop_back();
    	//delete temp;
    }
}


void PanelEditor::draw(sf::RenderTarget& app)
{
    app.draw(*this);
	for (unsigned int i = 0; i < m_vectButton.size(); i++)
    {
    	m_vectButton.at(i)->draw(app);
    }
}


void PanelEditor::addButton(ButtonPerso* button)
{
    unsigned int nbButton = m_vectButton.size();

    if(nbButton == 0)
    {
         float Y = (this->getLocalBounds().height - (button->getLocalBounds().height / 2)) / 2;
         int offsetY = int (this->getPosition().y) / 2;
         float X = this->getLocalBounds().width / 2 - button->getLocalBounds().width/ 2 + this->getPosition().x;

         button->setPosition(X, offsetY);
         m_vectButton.push_back(button);
    }
    else
    {
        m_vectButton.push_back(button);
        unsigned int nbButton = m_vectButton.size();

        float Y =  (this->getLocalBounds().height - (m_vectButton.front()->getLocalBounds().height / nbButton)) / nbButton ;
        int offsetY = int (Y) / nbButton;
        float X = this->getLocalBounds().width / 2 - m_vectButton.front()->getLocalBounds().width/ 2 + this->getPosition().x;

        for(unsigned int i = 0; i < m_vectButton.size(); i++)
        {
            m_vectButton.at(i)->setPosition(X, offsetY + (Y * i));
        }
    }
}

ButtonPerso* PanelEditor::popButton()
{
	//return m_vectButton.pop_back();
	//TODO
	return 0;
}


ButtonPerso* PanelEditor::deleteButton(unsigned int i)
{
	// TODO
	return 0;
}

ButtonPerso* PanelEditor::deleteButton(ButtonPerso* button)
{
	// TODO
	return 0;
}

void PanelEditor::manage(int coordMouseX, sf::RenderTarget& target)
{
    if(coordMouseX >= target.getSize().x*0.9)
    {
        m_visible = false;
        m_isAnimLeft = true;
        m_isAnimRight = false;
    }

    if(coordMouseX < target.getSize().x*0.9 )
    {
        m_visible = true;
        m_isAnimRight = true;
        m_isAnimLeft = false;
    }
}

void PanelEditor::handle_input(sf::Event& event, sf::RenderTarget& target)
{
	switch(event.type)
	{
		case sf::Event::MouseMoved:
		{
			int x = event.mouseMove.x /*- m_buttonCursor.getLocalBounds().width / 2*/;
			this->manage(x, target);
		}
		break;

        default:
		break;
	}

	for (unsigned int i = 0; i < m_vectButton.size(); i++)
	{
		m_vectButton.at(i)->handle_input(event, target);
	}
}

void PanelEditor::movePanel(sf::RenderTarget& target)
{
    int offset = 4;
    if(m_isAnimLeft && (this->getPosition().x + this->getGlobalBounds().width - offset) >= target.getSize().x)
    {
        if(m_timerPanel.getElapsedTime().asMilliseconds() > TimePanel)
        {
          	this->setPosition(this->getPosition().x - offset, this->getPosition().y);
            for (unsigned int i = 0; i < m_vectButton.size(); i++)
            {
            	sf::Vector2f coord = m_vectButton.at(i)->getPosition();
            	m_vectButton.at(i)->setPosition(coord.x - offset, coord.y);
            }
            m_timerPanel.restart();
        }
    }

    if(m_isAnimRight && (this->getPosition().x) < target.getSize().x)
    {
        if(m_timerPanel.getElapsedTime().asMilliseconds() > TimePanel)
        {
            this->setPosition(this->getPosition().x + offset, this->getPosition().y);
            for (unsigned int i = 0; i < m_vectButton.size(); i++)
            {
            	sf::Vector2f coord = m_vectButton.at(i)->getPosition();
            	m_vectButton.at(i)->setPosition(coord.x + offset, coord.y);
            }
            m_timerPanel.restart();
        }

    }
}

void PanelEditor::setAlpha (int _alpha)
{
    this->setColor(sf::Color(255, 255, 255, _alpha));
}
