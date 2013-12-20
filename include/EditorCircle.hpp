#ifndef EditorCircle_H
#define EditorCircle_H

#include <SFML/Graphics.hpp>

#include "../constants.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"


//std::string toString(TypeObject const& type) const;

/**
@brief : a wrapper class to manage different kind of object circleShape
**/

class EditorCircle : public sf::CircleShape
{
    public:
        EditorCircle();
        virtual ~EditorCircle();
        virtual float distance(sf::Vector2f pointOne, sf::Vector2f pointTwo);
        virtual bool isCollide(sf::Vector2f point);
        virtual bool isCollide(const sf::FloatRect& rect);
        virtual void draw(sf::RenderTarget& app);
        inline virtual TypeObject getType() const { return m_type;}
        std::string getTypeStr() const;
    protected:
    	TypeObject m_type;
};

#endif // EditorCircle_H
