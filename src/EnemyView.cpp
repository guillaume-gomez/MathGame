#include "EnemyView.hpp"
#include <sstream>

EnemyView::EnemyView(const EnemyModel& model, float scale)
:CharacterView(model,scale)
{
	m_nbAttempt.setColor(sf::Color(0,0,0,240));
	m_nbAttempt.setFont(14);
}

EnemyView::~EnemyView()
{
    //dtor
}

void EnemyView::draw( sf::RenderTarget& target)
{
	if(m_model.isAlive())
	{
		CharacterView::draw(target);
		m_nbAttempt.draw(target);
	}
}

void EnemyView::setStringAttempt( std::string str)
{
	m_nbAttempt.setString(str);
}

void EnemyView::show()
{
	CharacterView::show();

	//std::cout << " m_model-->" << &m_model <<"(" << m_model.getCoords().x <<" , " << m_model.getCoords().y << ") " << std::endl;
	sf::Vector2f pos =  m_model.getCoords() * m_scale;
	sf::FloatRect rect = m_animation.getLocalBounds();

	pos.x -=  (m_nbAttempt.getText().getLocalBounds().width / 2);
	pos.y = - pos.y - rect.height - (m_nbAttempt.getText().getLocalBounds().height / 2) - offsetNbAttemptEnemy;
	m_nbAttempt.setPosition(pos);

	//setStringAttempt Done in the upper class

}

EnemyView::EnemyView(const EnemyView& copy)
:CharacterView(copy.m_model,copy.m_scale)
 //share the same texture for all the instance
// m_ArtTexture(copy.m_ArtTexture)
{
	m_nbAttempt.setColor(sf::Color(0,0,0,240));
	m_nbAttempt.setFont(14);
}
