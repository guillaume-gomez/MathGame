#ifndef ENEMYVIEW_H
#define ENEMYVIEW_H

#include "CharacterView.hpp"
#include "EnemyModel.hpp"
#include "ManageText.hpp"


class EnemyView : public CharacterView
{
    public:
    EnemyView(const EnemyModel& model, float scale = 1.0f, int _w = 1, int _h = 1);
    virtual ~EnemyView();
    virtual void draw( sf::RenderTarget& target);
    void show();
    protected:
         ManageText m_nbAttempt;

};

#endif // ENEMYVIEW_H
