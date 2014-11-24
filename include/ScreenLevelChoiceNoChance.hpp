#ifndef SCREENLEVELCHOICENOCHANCE_H
#define SCREENLEVELCHOICENOCHANCE_H

#include "ScreenLevelChoice.hpp"


class ScreenLevelChoiceNoChance : public ScreenLevelChoice
{
    public:
        ScreenLevelChoiceNoChance(ScreenLink* stat);
        virtual ~ScreenLevelChoiceNoChance();
         int Run(sf::RenderWindow & App);
    protected:
    private:
};

#endif // SCREENLEVELCHOICENOCHANCE_H
