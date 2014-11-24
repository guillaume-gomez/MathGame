#include "Screen_Editor.hpp"

Screen_Editor::Screen_Editor(sf::RenderWindow& App, ScreenLink* link)
:m_editor(App), m_link(link)
{
     recenterCamera();
}

Screen_Editor::~Screen_Editor()
{
    //dtor
}

int Screen_Editor::Run(sf::RenderWindow& App)
{
    bool Running = true;
    m_editor.setBack(false);
    m_editor.setCenterCamera();
    m_editor.setSaving(false);


    while(Running)
    {
       Running =  m_editor.handleInput();

        if(m_editor.isBacked())
        {
            recenterCamera();
            Running = false;
            return MENU;
        }
        m_editor.move();
        m_editor.save(m_link);
        m_editor.show();
        m_editor.draw();
        App.display();
    }
    return (SCREEN_EXIT);
}

void Screen_Editor::recenterCamera()
{
    sf::View   viewPerso = m_editor.m_app.getView();
    viewPerso.reset(sf::FloatRect(0, 0, WindowWidth, WindowHeight));
	m_editor.m_app.setView(viewPerso);
}
