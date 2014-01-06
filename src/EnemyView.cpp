#include "EnemyView.hpp"

EnemyView::EnemyView(const EnemyModel& model, float scale, int _w, int _h)
:CharacterView(model,scale,_w,_h)
{
	  m_nbAttempt.setColor(sf::Color(0,0,0,200));
}

EnemyView::~EnemyView()
{
    //dtor
}

void EnemyView::draw( sf::RenderTarget& target)
{
	CharacterView::draw(target);
	m_nbAttempt.draw(target);
}

void EnemyView::show()
{
	CharacterView::show();

	sf::Vector2f pos =  m_model.getCoords();
	sf::FloatRect rect = m_animation.getLocalBounds();
	pos.x += (rect.width / 2);
	pos.y -= rect.height;
	m_nbAttempt.setPosition(pos);
	m_nbAttempt.setString(sf::String("3"/*m_model.getNbAttemptStr*/));
}

