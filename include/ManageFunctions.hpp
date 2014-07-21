#ifndef MANAGEFUNCTIONS_H
#define MANAGEFUNCTIONS_H

#include <SFML/Graphics.hpp>
#include "../constants.hpp"
#include "Curves.hpp"


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
        void resetToZero();
        std::string getFunction()const;
        const ConstrueFunction* getModelIndex();
        bool drawBefore(sf::RenderTarget& app);
        bool drawAfter(sf::RenderTarget& app);
        bool isEmpty() const;
    private:
    	bool m_changed;
        int m_currentIndex;
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

inline bool ManageFunctions::isEmpty() const
{
    return m_vectorCurves.empty();
}

#endif // MANAGEFUNCTIONS_H
