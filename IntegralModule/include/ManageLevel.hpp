#ifndef MANAGELEVEL_H
#define MANAGELEVEL_H

#include "../constants.hpp"
#include "../files.hpp"
#include "LevelView.hpp"
#include "LevelModel.hpp"
#ifdef DEBUG
	 #include <iostream>
#endif //DEBUG
#include <sstream>
#include <string>
#include "ScreenLink.hpp"
#include "ConstrueFunction.hpp"
#include "CharacterModel.hpp"
#include "SFML/Graphics/RenderTarget.hpp"



class ManageLevel
{
    public:
        float m_scale;

        ManageLevel( unsigned int _level = 1 , Difficulty _diff = Normal, float m_scale = 1.0f );
        void loadFile ( int numLevel, GameMode mode );
        void loadLevel ();
        virtual ~ManageLevel();
        void setLevel( int _level);
        unsigned int  getLevel( ) const;
        void IsNextLevel();
        int changeLevel ( ScreenLink * link);
        void reset();
        void drawPoints(sf::RenderTarget& app);
        void drawUI(sf::RenderTarget& app);
        std::string convertEnum ( Difficulty _diff);
        void displaying(sf::Event& event , sf::RenderTarget& target , sf::View& myView);
        void levelFinished ( CharacterModel& charModel,bool& soundPlayable);
        void setToolTipPos (sf::Vector2f _temp);
        sf::Vector2f getToolTipPos ()const;
        void setToolTipScale (sf::Vector2f _scale);
        sf::Vector2f getToolTipScale ()const;
        void decrementAttempt();
        bool getChangeLevel()const ;
        void displayNbAttempt();
        void setnbAttempTextPosition( sf::Vector2f _pos);
        void setnbAttempTextScale( sf::Vector2f _pos);
        void setDiff(Difficulty _diff);
    private:
        Difficulty m_difficulty;
        unsigned int m_levelCurrent;
        std::string m_filenameCurrent;
        bool m_changeLevel;
        LevelView* m_LevelView;
        LevelModel* m_LevelModel;

        sf::Sprite m_tooltip;
        bool m_isDisplayToolTip;

        sf::Text m_text;
        sf::Font m_font;
        sf::String m_string;
        sf::Text m_nbAttemp;

        static sf::Texture toolTipTex;
        static bool toolTipTexLoaded;
        static bool loadToolTipTex(const char* filenametoolTipTex = FilenameToolTipTex);



};

/*********************************************************/
//       Accessors
/*********************************************************/

inline void ManageLevel::setLevel( int _level)
{
    m_levelCurrent = _level;
}

inline unsigned int  ManageLevel::getLevel( ) const
{
    return m_levelCurrent;
}

inline void ManageLevel::setToolTipPos (sf::Vector2f _temp)
{
    m_tooltip.setPosition(_temp);
}

inline sf::Vector2f ManageLevel::getToolTipPos ()const
{
    return m_tooltip.getPosition();
}

inline void ManageLevel::setToolTipScale (sf::Vector2f _scale)
{
    m_tooltip.setScale(_scale);
}

inline sf::Vector2f ManageLevel::getToolTipScale ()const
{
    return m_tooltip.getScale();
}


inline void ManageLevel::decrementAttempt(){ m_LevelModel->decrementAttempt(); };

inline bool ManageLevel::getChangeLevel()const {return m_changeLevel;};

inline void ManageLevel::setnbAttempTextPosition( sf::Vector2f _pos)
{
    m_nbAttemp.setPosition(_pos);
};

inline void ManageLevel::setnbAttempTextScale( sf::Vector2f _pos)
{
    m_nbAttemp.setScale(_pos);
};

inline void ManageLevel::setDiff(Difficulty _diff)
{
    m_difficulty = _diff;
}

/*********************************************************/
//      Accessors
/********************************************************/

#endif // MANAGELEVEL_H
