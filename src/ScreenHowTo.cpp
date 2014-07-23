#include "ScreenHowTo.hpp"

#include <cstdint>

ScreenHowTo::ScreenHowTo()
: m_quit(false),
  m_nbInstruction(10),
  m_currentInstruction(0)
{

    loadFileInstruction();

    m_background.setTexture(*TextureManager::getTextureManager()->getResource(std::string(FilenameBackGroundMenu)));
    m_background.setColor(sf::Color(backgroundColor,backgroundColor,backgroundColor));

    m_window = sfg::Window::Create();
    m_window->SetTitle( "How To Play at I Hate Math" );

    m_next = sfg::Button::Create("Next");
    m_previous = sfg::Button::Create("Previous");

    m_image = sfg::Image::Create();
    m_image->SetRequisition(sf::Vector2f(300.0f,300.0f));

    sf::Image image;
    image.loadFromFile(std::string(FilenameButtonOption));
    m_image->SetImage(image);

    m_box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    m_boxImages = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    m_boxLabel = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);

    m_boxImages->Pack(m_previous);
    m_boxImages->Pack(m_image);
    m_boxImages->Pack(m_next);

    m_previous->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&ScreenHowTo::previousClick, this));
    m_next->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&ScreenHowTo::nextClick, this));

    m_label = sfg::Label::Create("Nothing to say For the moment");
    m_label->SetId("TextHowTo");
    //m_label->SetLineWrap(true);
    m_boxLabel->Pack(m_label);


    m_box->Pack(m_boxImages);
    m_box->Pack(m_boxLabel);

   m_window->Add(m_box);
   m_desktop.Add(m_window);

}

void ScreenHowTo::loadFileInstruction()
{
    std::ifstream file;
    file.open(FilenameInfoHowTo);
    if(file.is_open())
    {
        file >> m_nbInstruction;
        file.clear();
        file.ignore(INTMAX_MAX,'\n');

        for(int i = 0; i < m_nbInstruction; i++)
        {
            std::string string;
            getline(file, string, '#');
            m_filenameImages.push_back(string);
            //std::cout << string << std::endl;
            file.clear();
            file.ignore(INTMAX_MAX,'\n');
            getline(file, string, '#');
            //std::cout << string << std::endl;
            file.clear();
            file.ignore(INTMAX_MAX,'\n');
            m_instructions.push_back(string);
        }
        std::cout << "File loaded" << std::endl;
    }
    else
    {
        #ifdef DEBUG
            std::cerr << "Error file :'" <<FilenameInfoHowTo<< "' cannot exist" << std::endl;
        #endif
        std::runtime_error("Cannot load the file\n");
        file.close();
    }

    file.close();
}

void ScreenHowTo::previousClick()
{
    m_currentInstruction--;
    if( m_currentInstruction < 0)
    {
        m_currentInstruction = m_nbInstruction - 1;
    }

    loadInstruction();
}


void ScreenHowTo::nextClick()
{
    m_currentInstruction++;
    if(m_currentInstruction >= m_nbInstruction)
    {
        m_currentInstruction = 0;
    }

    loadInstruction();

}

void ScreenHowTo::loadInstruction()
{
    sf::Image image;
    image.loadFromFile(m_filenameImages.at(m_currentInstruction));
    std::cout << "+++++++++++++++++++++++++++" << std::endl;
    std::cout << m_filenameImages.at(m_currentInstruction) << std::endl;
    std::cout << m_instructions.at(m_currentInstruction) << std::endl;
    m_image->SetImage(image);

    m_label->SetText(m_instructions.at(m_currentInstruction));
}

int ScreenHowTo::Run( sf::RenderWindow &App)
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
                else if(event.key.code == sf::Keyboard::Left)
                {
                    previousClick();
                }
                else if(event.key.code == sf::Keyboard::Right)
                {
                    nextClick();
                }
            }

            if(m_quit)
            {

                m_window->Show(false);
                m_quit = false;
                return MENU;
            }
        }

        m_desktop.Update( 0.f );

		App.clear();
        App.draw(m_background);
		m_sfgui.Display( App );
		App.display();
	}
return (SCREEN_EXIT);
}

ScreenHowTo::~ScreenHowTo()
{
    //dtor
}
