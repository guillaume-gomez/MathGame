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
        const ConstrueFunction* getModelIndex();
    private:
    	bool m_changed;
    	int m_currentIndex;
    	std::vector<Curves> m_vectorCurves;
};


inline bool ManageFunctions::isChanged() const
{
    return m_changed;
}

#endif // MANAGEFUNCTIONS_H
