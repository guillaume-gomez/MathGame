#include "EditorObject.hpp"

EditorObject::EditorObject()
{

}

EditorObject::~EditorObject()
{
    //dtor
}

void EditorObject::draw(sf::RenderTarget& app)
{
    app.draw(*this);
}



