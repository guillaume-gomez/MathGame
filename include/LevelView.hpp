#ifndef LEVELVIEW_H
#define LEVELVIEW_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "LevelModel.hpp"
#ifdef DEBUG
	 #include <iostream>
#endif //DEBUG
#include <vector>
#include <string>


#include "../files.hpp"

class LevelView
{
    public:
        LevelView(const LevelModel& model,  float _scale);
        virtual ~LevelView();
        void draw( sf::RenderTarget& target );
        std::vector<sf::Sprite> getSpriteList () const;
        void loadCoord();
    private:
        LevelView();
        static sf::Texture m_texNormal;
        static sf::Texture m_texGoal;
        static bool TexturesLoaded;
        static bool loadTex(const char* _filenameNormalText = FilenameNormalPointTex , const char* _filenameGoalText = FilenamePointGoalTex);

        const LevelModel& m_model;
        float m_scale;
        std::vector<sf::Sprite> m_listSprite;

};

/****************************************************
**
******************************************************/

inline std::vector<sf::Sprite> LevelView::getSpriteList () const { return m_listSprite;};


/****************************************************
**
******************************************************/

#endif // LEVELVIEW_H
