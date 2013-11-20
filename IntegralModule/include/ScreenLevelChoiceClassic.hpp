#ifndef SCREENLEVELCHOICECLASSIC_H
#define SCREENLEVELCHOICECLASSIC_H

#include "ScreenLevelChoice.hpp"

class ScreenLevelChoiceClassic : public ScreenLevelChoice
{
    public:
        ScreenLevelChoiceClassic(ScreenLink* stat);
        virtual ~ScreenLevelChoiceClassic();
        int Run(sf::RenderWindow & App);
    protected:
    private:
};

#endif // SCREENLEVELCHOICECLASSIC_H
