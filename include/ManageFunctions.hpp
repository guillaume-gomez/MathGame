#ifndef MANAGEFUNCTIONS_H
#define MANAGEFUNCTIONS_H

#include <SFML/Graphics.hpp>

#include "Curves.hpp"
#include "../constants.hpp"

class ManageFunctions
{
    public:
        ManageFunctions();
        virtual ~ManageFunctions();
        void handle_input(sf::Event& event);
        void draw(sf::RenderTarget& app);
        void addFunction(std::string function);
        void represent(float step);
        bool isChanged() const;
        void reset();
        std::string getFunction()const;
        const ConstrueFunction* getModelIndex();
        void setViews(const sf::View view);
    private:
    	bool m_changed;
    	unsigned int m_currentIndex;
    	std::vector<Curves> m_vectorCurves;
};


inline bool ManageFunctions::isChanged() const
{
    return m_changed;
}

inline std::string ManageFunctions::getFunction() const
{
    return m_vectorCurves.at(m_currentIndex).getFunction();
}

#endif // MANAGEFUNCTIONS_H
