#ifndef LEVELVIEW_H
#define LEVELVIEW_H

#ifdef DEBUG
	 #include <iostream>
#endif //DEBUG
#include <string>
#include <vector>
#include <stdexcept>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../files.hpp"
#include "Enemy.hpp"
#include "Integral.hpp"
#include "LevelModel.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"
#include "GravityCircle.hpp"
#include "InfoDisplayer.hpp"
#include "ManageFunctions.hpp"
#include "Point.hpp"


class LevelView
{
    public:
        LevelView(const LevelModel& model,  float _scale);
        virtual ~LevelView();
        void draw( sf::RenderTarget& target );
        std::vector<EditorObject*> getSpriteList () const;
        void loadCoord();
        void reset();

        void setView(sf::View& view);
    private:
        LevelView();
        std::vector<EditorObject*> m_listSprite;
        std::vector<std::string> m_listFunctionLevel;
        const LevelModel& m_model;
        static sf::Texture m_texNormal;
        static sf::Texture m_texGoal;
        float m_scale;
        static bool TexturesLoaded;
        static bool loadTex(const char* _filenameNormalText = FilenameNormalPointTex, const char* _filenameGoalText = FilenamePointGoalTex);

        sf::View m_view;
};

/****************************************************
**
******************************************************/

inline std::vector<EditorObject*> LevelView::getSpriteList () const { return m_listSprite;};

inline void LevelView::setView(sf::View& view)
{
    m_view = view;
}

/****************************************************
**
******************************************************/

#endif // LEVELVIEW_H
