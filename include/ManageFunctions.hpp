#ifndef MANAGEFUNCTIONS_H
#define MANAGEFUNCTIONS_H

#include <SFML/Graphics.hpp>

#include "ConstrueFunction.hpp"
#include "GraphView.hpp"

class ManageFunctions
{
    public:
        ManageFunctions();
        virtual ~ManageFunctions();
        void handle_input(sf::Event& event);
        void draw(sf::RenderTarget& app);
        void addFunction(std::string function);
        void represent(float step);
    private:
    	bool m_changed;
    	unsigned int currentIndex;
    	std::vector<ConstrueFunction> m_vectorModel;
    	GraphView m_view;
};

#endif // MANAGEFUNCTIONS_H
