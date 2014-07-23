#ifndef INFODISPLAYER_H
#define INFODISPLAYER_H

#include "EditorObject.hpp"
#include "../libs/TextAreaSFML2_0.hpp"

class InfoDisplayer : public EditorObject
{
    public:
        InfoDisplayer();
        virtual ~InfoDisplayer();
        InfoDisplayer(const InfoDisplayer& copy);

        void setMessage(std::string message);
        std::string getMessage() const;
        virtual void draw(sf::RenderTarget& app);
        virtual EditorObject* clone() const;
    	virtual void setPosition(float x, float y);
    	virtual void setPosition(sf::Vector2f& pos);
        virtual sf::FloatRect get_GlobalBounds() const;
        virtual sf::Vector2f get_Position() const;
        virtual std::string save(float scale = GraphScale) const;
        virtual EditorObject* loadView(const Element& elmt, float scale);

    private:
        std::string m_message;
        TextAreaSFML2_0 m_area;

};


inline void InfoDisplayer::setMessage(std::string message)
{
    m_message = message;
    m_area.setString(m_message);
}


inline std::string InfoDisplayer::getMessage() const
{
    return m_message;
}


#endif // INFODISPLAYER_H
