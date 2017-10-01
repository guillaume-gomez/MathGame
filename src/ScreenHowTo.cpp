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
    m_image->SetRequisition(sf::Vector2f(400.0f,300.0f));

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
    m_boxLabel->Pack(m_label);


    m_box->Pack(m_boxImages);
    m_box->Pack(m_boxLabel);

    m_window->Add(m_box);
    m_desktop.Add(m_window);

    loadInstruction();

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
    image = Resize(image, true, sf::Vector2u(400,300));
    //  std::cout << "+++++++++++++++++++++++++++" << std::endl;
    //  std::cout << m_filenameImages.at(m_currentInstruction) << std::endl;
    //  std::cout << m_instructions.at(m_currentInstruction) << std::endl;
    m_image->SetImage(image);

    std::string temp = m_instructions.at(m_currentInstruction);
    std::basic_string<sf::Uint32> utf32;
    sf::Utf8::toUtf32(temp.begin(), temp.end(), std::back_inserter(utf32));

    m_label->SetText(utf32);
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


sf::Image ScreenHowTo::Resize( sf::Image CurrentImage, bool m_KeepAspect, const sf::Vector2u& customSize)
{
// If no size is given (0,0) , use original image...
    if( !customSize.x || !customSize.y )
    {
        return CurrentImage;
    }
    // Let the flood begin
    float originalX = static_cast<float>( CurrentImage.getSize().x );
    float originalY = static_cast<float>( CurrentImage.getSize().y );
    float desiredX = static_cast<float>( customSize.x );
    float desiredY = static_cast<float>( customSize.y );
    // Compute the scale we will apply to image
    float scaleX = desiredX / originalX;
    float scaleY = desiredY / originalY;
    // Get texture of the original image
    sf::Texture tempTexture;
    tempTexture.loadFromImage( CurrentImage );
    // Sprite allows transformations to be made to it, so let's assign our texture to it
    // (warn: sprite doesn't own the texture, keep it alive till we're done)
    sf::Sprite tempSprite;
    tempSprite.setTexture( tempTexture, true );
    if( m_KeepAspect )
    {
        // Use same scale for both sides of the sprite
        float lowerScale = std::min( scaleX, scaleY );
        tempSprite.scale( lowerScale, lowerScale );
        // Since the image will not be stretched out because we want to keep the aspect of the
        // image, there will be an empty space to the right/down of the resized image. I think
        // it's better if the empty place is distributed around the resized image on all sides,
        // so we move the sprite to the center of the rectangle we set by size we want.
        //
        float offsetX = ( desiredX - ( originalX * ( lowerScale ) ) ) / 2;
        float offsetY = ( desiredY - ( originalY * ( lowerScale ) ) ) / 2;
        tempSprite.move( offsetX, offsetY );
    }
    else
    {
        tempSprite.scale( scaleX, scaleY );
    }
    // Transformations on Sprite are set, so we can pre-render the sprite on
    // a new texture with a transparent background
    sf::RenderTexture tempRenderTexture;
    tempRenderTexture.create( customSize.x, customSize.y );
    tempRenderTexture.setSmooth( true );
    tempRenderTexture.clear( sf::Color( 255,255,255,0 ) );
    tempRenderTexture.draw( tempSprite );
    tempRenderTexture.display();
    // Now when we have the new texture with our resized image ready
    // we can set it as a new image to the underlying base Image
    // class, and we are done.
    return  tempRenderTexture.getTexture().copyToImage();
}


ScreenHowTo::~ScreenHowTo()
{
    //dtor
}
