#ifndef ADDINTEGRALBUTTON_HPP
#define ADDINTEGRALBUTTON_HPP

#include <SFGUI/SFGUI.hpp>
#include "ButtonPerso.hpp"

class AddIntegralButton : public ButtonPerso
{
    public:
        AddIntegralButton(const char* _filename);
        void addToWindow(sfg::Window::Ptr window);
        virtual ~AddIntegralButton();
    private:
        sfg::Box::Ptr m_layout;
        sfg::Adjustment::Ptr m_adjustment;
};

#endif // ADDINTEGRALBUTTON_HPP
