#ifndef SCREEN_EDITOR_H
#define SCREEN_EDITOR_H

#include "Screen.hpp"
#include "../constants.hpp"
#include "Editor.hpp"
#include "ScreenLink.hpp"

class Screen_Editor : public Screen
{
    public:
        Screen_Editor(sf::RenderWindow& App, ScreenLink* link );
        virtual ~Screen_Editor();
        void recenterCamera();
        int Run(sf::RenderWindow& App);
    private:
        Editor m_editor;
        ScreenLink* m_link;
};

#endif // SCREEN_EDITOR_H
