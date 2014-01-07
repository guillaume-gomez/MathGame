#include "EnemyView.hpp"

EnemyView::EnemyView(const EnemyModel& model, float scale, int _w, int _h)
:CharacterView(model,scale,_w,_h)
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

void EnemyView::show()
{
	CharacterView::show();

	sf::Vector2f pos =  m_model.getCoords() * m_scale;
	sf::FloatRect rect = m_animation.getLocalBounds();

	pos.x -=  (m_nbAttempt.getText().getLocalBounds().width / 2);
	pos.y = - pos.y - rect.height - (m_nbAttempt.getText().getLocalBounds().height / 2) - offsetNbAttemptEnemy;
	m_nbAttempt.setPosition(pos);

	const EnemyModel* m_modelEnemyTemp = dynamic_cast<const EnemyModel*>(&m_model);
	if(m_modelEnemyTemp != nullptr)
	{
        m_nbAttempt.setString(sf::String(m_modelEnemyTemp->getNbAttemptStr()));
    }
    else
    {
        std::runtime_error("void EnemyView::show() : Cannot dynamic_cast<const EnemyModel*>(&m_model)");
    }
}

