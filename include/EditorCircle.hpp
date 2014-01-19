#ifndef EditorCircle_H
#define EditorCircle_H

#include <SFML/Graphics.hpp>

#include "EditorObject.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"


//std::string toString(TypeObject const& type) const;

/**
@brief : a wrapper class to manage different kind of object circleShape
**/

class EditorCircle : public sf::CircleShape , public EditorObject
{
    public:
        EditorCircle();
        virtual ~EditorCircle();
        virtual float distance(sf::Vector2f pointOne, sf::Vector2f pointTwo);
        virtual bool isCollide(sf::Vector2f point);
        virtual bool isCollide(const sf::FloatRect& rect);
        virtual void draw(sf::RenderTarget& app);
        virtual EditorObject* clone() const = 0;
        virtual void set_Position(sf::Vector2f& pos);
    	virtual void set_Position(float x, float y);
    	virtual sf::Vector2f get_Position() const ;
    	virtual sf::FloatRect get_GlobalBounds() const;
        virtual std::string save(float scale = GraphScale) const;
    protected:

};


inline void EditorCircle::set_Position(sf::Vector2f& pos) { this->setPosition(pos);};

inline void EditorCircle::set_Position(float x, float y) { this->setPosition(x,y);};

inline sf::Vector2f EditorCircle::get_Position() const { return this->getPosition();};

inline  sf::FloatRect EditorCircle::get_GlobalBounds() const { return this->getGlobalBounds();};


#endif // EditorCircle_H
