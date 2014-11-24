#include "Screen.hpp"

bool Screen::isloadTheme = false;

Screen::Screen()
: m_desktop()
{
    if(!isloadTheme)
    {
//        std::cout << "load " << std::endl;
        m_desktop.LoadThemeFromFile(FilenameTheme);
//        std::cout << "end" << std::endl;
        isloadTheme = true;
    }
}

Screen::~Screen()
{
    //dtor
}
