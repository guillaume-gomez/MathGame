#ifndef ENEMYVIEW_H
#define ENEMYVIEW_H

#include "CharacterView.hpp"
#include "EnemyModel.hpp"
#include "ManageText.hpp"


class EnemyView : public CharacterView
{
    public:
    EnemyView(const EnemyModel& model, float scale = 1.0f);
    virtual ~EnemyView();
    virtual void draw( sf::RenderTarget& target);
    void show();
    void setStringAttempt( std::string str);
    protected:
         ManageText m_nbAttempt;
    private:
    	EnemyView(const EnemyView& copy);
};

#endif // ENEMYVIEW_H
