#ifndef ADDINTEGRALBUTTON_HPP
#define ADDINTEGRALBUTTON_HPP

#include <SFGUI/SFGUI.hpp>
#include "ButtonPerso.hpp"

class AddIntegralButton : public ButtonPerso
{
    public:
        AddIntegralButton(const char* _filename);
        void addToWindow(sfg::Window::Ptr window);
        void handle_input(sf::Event& event, sf::RenderTarget& target);
        void hide();
        void update();
        virtual ~AddIntegralButton();
    private:
        sfg::Window::Ptr m_window;
        sfg::Box::Ptr m_layout;
        sfg::Adjustment::Ptr m_adjustment;
        sfg::ComboBox::Ptr m_min_combo_box;
        sfg::ComboBox::Ptr m_max_combo_box;
        sfg::Button::Ptr m_button;
};

#endif // ADDINTEGRALBUTTON_HPP
