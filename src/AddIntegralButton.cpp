#include "AddIntegralButton.hpp"

AddIntegralButton::AddIntegralButton(const char* _filename)
: StaticButton(_filename)
{
    m_window = sfg::Window::Create();
    m_window->SetTitle("Test");
    m_layout = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    const char* items[] = {"-25", "-24", "-23", "-22", "-21", "-20", "-19", "-18", "-17", "-16", "-15", "-14", "-13", "-12", "-11", "-10", "-9", "-8", "-7", "-6", "-5", "-4", "-3", "-2", "-1", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25"};
    m_min_combo_box = sfg::ComboBox::Create();
    m_max_combo_box = sfg::ComboBox::Create();
    m_min_combo_box->SetRequisition(sf::Vector2f(20.f, 10.f));
    m_max_combo_box->SetRequisition(sf::Vector2f(20.f, 10.f));
    for(auto i = 0; i < 51; ++i)
    {
        m_min_combo_box->AppendItem(items[i]);
        m_max_combo_box->AppendItem(items[i]);
    }
    m_button = sfg::Button::Create("Add");
    m_button->GetSignal(sfg::ToggleButton::OnLeftClick).Connect(std::bind(&AddIntegralButton::addIntegral, this));
    m_layout->Pack(m_min_combo_box);
    m_layout->Pack(m_max_combo_box);
	m_layout->Pack(m_button);
    m_layout->SetSpacing(10.f);

    m_window->Add(m_layout);
    m_window->SetPosition(sf::Vector2f(200.0f, 420.0f));
    hide();
}

void AddIntegralButton::update()
{
    m_window->Update(0.0f);
}


void AddIntegralButton::hide()
{
    m_window->Show(false);
}

void AddIntegralButton::handle_input(sf::Event& event, sf::RenderTarget& target)
{
    StaticButton::handle_input(event, target);
    if(m_clicked) {
        m_window->Show(true);
    }
    m_window->HandleEvent(event);
}

void AddIntegralButton::addIntegral()
{
    //std::cout << static_cast<std::string>(m_min_combo_box->GetSelectedText()) << " " << static_cast<std::string>(m_max_combo_box->GetSelectedText()) << std::endl;
    hide();
}

AddIntegralButton::~AddIntegralButton()
{
    //dtor
}
