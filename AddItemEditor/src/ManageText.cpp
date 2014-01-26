#include "ManageText.hpp"

ManageText::ManageText()
:m_changed(false), m_sizeFont(Font), m_isTyping(false), m_jumpable(false), m_toResize(0)
{
    if (!m_font.loadFromFile(FilenameFont))
    {
    	#ifdef DEBUG
			std::cerr << "Error : ManageText::ManageText()" << std::endl;
    	#endif // DEBUG
    }
    m_text.setCharacterSize(m_sizeFont);
    m_text.setFont(m_font);
}


ManageText::~ManageText()
{
    //dtor
}

/**
*@brief : Draw the string
**/
void ManageText::draw(sf::RenderTarget& App)
{
    m_text.setString(m_string);
   App.draw(m_text);
}


 void ManageText::handle_input(const sf::Event &event, GraphView& view)
 {
    m_isTyping = false;
    if(event.type == sf::Event::KeyPressed)
    {
     	switch(event.key.code)
     	{
		case sf::Keyboard::BackSpace:
		    m_isTyping = true;
			if(m_string.getSize() > 0)
            {
                 if ( m_string[m_string.getSize() - 1] == '\n')
                {
                    m_toResize = -1;
                }

				m_string.erase(m_string.getSize() - 1);
				m_changed = true;
            }
			break;

		default:
			break;
     	}
     }

     if(event.type == sf::Event::TextEntered)
     {
     	if(isprint(event.text.unicode))
		{
         sf::String temp(event.text.unicode);
         m_string += temp;
         m_changed = true;
         m_isTyping = true;
		}
     }
	m_text.setString(m_string);

 }

 std::ostream& operator<<(std::ostream &flux, const ManageText&  texte)
 {
     flux <<" x = "<< texte.m_text.getPosition().x << " y = " << texte.m_text.getPosition().y << std::endl;
     flux << " width = " << texte.m_text.getLocalBounds().width << " height = " << texte.m_text.getLocalBounds().height << std::endl;
     return flux;
 }
