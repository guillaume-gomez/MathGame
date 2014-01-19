#ifndef ENEMY_H
#define ENEMY_H

#include "EditorObject.hpp"
#include "EnemyModel.hpp"
#include "EnemyView.hpp"

class Enemy : public EditorObject
{
    public:
        Enemy();
        Enemy(const Enemy& copy);
        virtual ~Enemy();
        virtual const EnemyModel& getModel();
        virtual const EnemyView& getView();
        virtual void handle_input(const sf::Event& event, const TextAreaSFML2_0& textAreaFunction);
        virtual void show();
        virtual void draw(sf::RenderTarget& app);
        virtual void reset();
        void setMoveType(CharacterModel::MoveType moveType);
        void setFrictionCoefficient(float frictionCoefficient);
        void setTexture(const sf::Texture* texture, int frameWidth, int frameHeight);
        void playSound();
        void decrementAttempt();
        void setNbAttempt(unsigned int i);
        unsigned int getNbAttempt() const;
        virtual sf::Vector2f get_Position() const;
        virtual void set_Position(sf::Vector2f& pos);
        virtual void set_Position(float x, float y);
        virtual sf::FloatRect get_GlobalBounds() const;
        virtual EditorObject* clone() const;
        virtual std::string save(float scale = GraphScale) const;
    private:
        EnemyModel m_model;
        EnemyView m_view;
};


inline const EnemyModel& Enemy::getModel() { return m_model;}

inline const EnemyView& Enemy::getView() { return m_view;}

inline unsigned int Enemy::getNbAttempt() const {return m_model.getNbAttempt();}

inline void Enemy::decrementAttempt()
{
    m_model.decrementAttempt();
}

inline void Enemy::setNbAttempt(unsigned int value)
{
    m_model.setNbAttempt(value);
}
//
// had to be used only for the editor, during the game, the model define it position
//
inline void Enemy::set_Position(sf::Vector2f& pos) {m_model.setCoords(pos);};
inline void Enemy::set_Position(float x, float y) {m_model.setCoords(x,y);};

inline sf::Vector2f Enemy::get_Position() const { return m_model.getCoords();};

inline sf::FloatRect Enemy::get_GlobalBounds() const{ return m_view.getGlobalBounds();};


#endif // ENEMY_H
