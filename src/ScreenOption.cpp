#include "ScreenOption.hpp"


//std::vector<Button*> m_listButton;
//

std::string ScreenOption::m_filenameChar = FilenameDefaultChar;


ScreenOption::ScreenOption(unsigned int _button)
: m_nbButton(_button), m_gravityType(NoSliding), m_character_array(0)
{

   m_window = sfg::Window::Create();
   m_window->SetTitle( "Option" );

   m_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
   m_layoutPhysics = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL);
   m_layoutCharacter = sfg::Box::Create( sfg::Box::Orientation::HORIZONTAL);

   m_framePhysics = sfg::Frame::Create("Gravity Type");
   m_frameCharacter = sfg::Frame::Create("Select a character");

   m_background.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameBackGroundMenu)));
   m_background.setColor(sf::Color(backgroundColor,backgroundColor,backgroundColor));

    for ( unsigned int i = 0 ; i < m_nbButton ; i++)
    {
        ChoiceCharacter temp = ChoiceCharacter(i+1);
        m_character_array.push_back(temp);
        sfg::Button::Ptr button (sfg::Button::Create("Character"));
        button->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind(&ChoiceCharacter::defineCharacter , &(m_character_array.at(i))));
        m_layoutCharacter->Pack(button);

    }

    sfg::RadioButton::Ptr radio1(sfg::RadioButton::Create("Sliging"));
    sfg::RadioButton::Ptr radio2(sfg::RadioButton::Create("No Sliding", radio1->GetGroup()));
    radio1->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&ScreenOption::desactivateSliding, this));
    radio2->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&ScreenOption::activateSliding, this));

    sfg::Button::Ptr saveButton(sfg::Button::Create("Save"));
    saveButton->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&ScreenOption::save, this));

    m_layoutPhysics->Pack(radio1);
    m_layoutPhysics->Pack(radio2);

    m_frameCharacter->Add(m_layoutCharacter);
    m_framePhysics->Add(m_layoutPhysics);

    m_box->Pack(m_frameCharacter);
    m_box->Pack(m_framePhysics);
    m_box->Pack(saveButton);

	m_window->Add(m_box);


}

void ScreenOption::desactivateSliding()
{
    m_gravityType = NoSliding;
}

void ScreenOption::activateSliding()
{
    m_gravityType = Sliding;
}

void ScreenOption::save()
{
    std::string filename ;
	unsigned int width = 0;
    unsigned int height = 0;
    float friction;
    std::ofstream configFile(FilenameConfigFile);


    if(m_filenameChar == FilenameDefaultChar)
    {
        friction = DefautCharFriction;
        width = DefaultCharWidth;
        height = DefaultCharHeight;
    }
    else if(m_filenameChar == FilenameBike)
    {
        friction = Bikefriction;
        width = BikeWidth ;
        height = BikeHeight;
    }

    std::cout << m_filenameChar << std::endl;
    configFile <<"FilenameCharacterTex = "<< m_filenameChar << std::endl;
    configFile << "width = "<< width << std::endl;
    configFile << "height = "<< height<< std::endl;
    configFile << "MoveType = "<<m_gravityType << std::endl;
    configFile << "FrictionCoefficient = "<<friction << std::endl;

    // std::cout << "Saved" << std::endl;
}


int ScreenOption::Run( sf::RenderWindow& App)
{
	bool Running = true;

    App.resetGLStates();

    m_window->SetPosition(sf::Vector2f(App.getSize().x / 2.0f - m_window->GetAllocation().width /2.0f, App.getSize().y / 2.0f - m_window->GetAllocation().height /2.0f));
    m_window->Show(true);
	while(Running)
	{
		sf::Event event;
		//Verifing events
		while(App.pollEvent(event))
		{
            m_window->HandleEvent( event );

            if(event.type == sf::Event::Closed)
            {
                Running = false;
                App.close();
            }

            if( event.type == sf::Event::KeyPressed)
            {
                if( event.key.code == sf::Keyboard::Escape)
                {
                     m_window->Show(false);
                     return MENU;
                }
            }
        }

        m_window->Update( 0.f );

		App.clear();
		App.draw(m_background);
		m_sfgui.Display( App );
		App.draw(currentChoice);
		App.display();
        currentChoice.Update();
	}
return (SCREEN_EXIT);
}


ScreenOption::~ScreenOption()
{}

ChoiceCharacter::ChoiceCharacter(unsigned int type)
:m_type(type)
{}

ChoiceCharacter::~ChoiceCharacter()
{}

void ChoiceCharacter::defineCharacter()
{
    switch(m_type)
    {
        case 1:
            ScreenOption::m_filenameChar = FilenameDefaultChar;
        break;
        case 2:
            ScreenOption::m_filenameChar = FilenameBike;
        break;
    }

}
