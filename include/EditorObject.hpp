#ifndef EDITOROBJECT_H
#define EDITOROBJECT_H

#include <string>

#include <SFML/Graphics.hpp>

#include "../constants.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"

/**
@brief : a wrapper class to manage different kind of object
**/

class EditorObject
{
    public:
        EditorObject();
        virtual ~EditorObject();
        virtual void draw(sf::RenderTarget& app) = 0;
        inline virtual TypeObject getType() const { return m_type;}
        std::string getTypeStr() const ;
        static std::string getTypeStr(const TypeObject& type);
        static bool compare(const EditorObject* r1, const EditorObject* r2);
        virtual EditorObject* clone() const = 0;
        virtual void set_Position(sf::Vector2f& position) = 0;
        virtual void set_Position(float x, float y) = 0;
        virtual sf::FloatRect get_GlobalBounds() const = 0;
        virtual sf::Vector2f get_Position() const = 0;
        virtual std::string save(float scale = GraphScale) const = 0;

    protected:
        static const std::map<TypeObject, int> objectValueMap;
    	TypeObject m_type;
    private:
};

#endif // EDITOROBJECT_H
