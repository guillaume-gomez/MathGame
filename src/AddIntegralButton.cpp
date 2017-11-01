#include "AddIntegralButton.hpp"

AddIntegralButton::AddIntegralButton(const char* _filename)
: ButtonPerso(_filename)
{
    m_layout = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
	auto scale = sfg::Scale::Create(sfg::Scale::Orientation::HORIZONTAL);
	auto scrollbar = sfg::Scrollbar::Create(sfg::Scrollbar::Orientation::VERTICAL);

	m_adjustment = scrollbar->GetAdjustment();
	scale->SetAdjustment(m_adjustment);

	// Tune the adjustment parameters.
	m_adjustment->SetLower(20.f);
	m_adjustment->SetUpper(100.f);

	m_adjustment->SetMinorStep(3.f);
	m_adjustment->SetMajorStep(12.f);

	m_adjustment->SetPageSize(20.f);

	//m_adjustment->GetSignal( sfg::Adjustment::OnChange ).Connect( std::bind( &RangeExample::AdjustmentChange, this ) );

	scale->SetRequisition(sf::Vector2f(80.f, 20.f));
	scrollbar->SetRequisition(sf::Vector2f(0.f, 80.f));

	auto scalebox = sfg::Box::Create( sfg::Box::Orientation::VERTICAL );
	scalebox->Pack(scale, false, false);

	m_layout->Pack(scalebox);
	m_layout->Pack(scrollbar);
	// Set box spacing
	m_layout->SetSpacing(5.f);
}

void AddIntegralButton::addToWindow(sfg::Window::Ptr window)
{
    window->Add(m_layout);
}

AddIntegralButton::~AddIntegralButton()
{
    //dtor
}
