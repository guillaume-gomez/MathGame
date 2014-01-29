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
#include "Curves.hpp"
#include "Integral.hpp"
#include "LevelModel.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"
#include "GravityCircle.hpp"
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
        unsigned int getNbCurves() const;
        std::string getFunction(unsigned int index) const ;
    private:
        LevelView();
        std::vector<EditorObject*> m_listSprite;
        std::vector<Curves*> m_listFunctionLevel;
        const LevelModel& m_model;
        static sf::Texture m_texNormal;
        static sf::Texture m_texGoal;
        float m_scale;
        static bool TexturesLoaded;
        static bool loadTex(const char* _filenameNormalText = FilenameNormalPointTex, const char* _filenameGoalText = FilenamePointGoalTex);

};

/****************************************************
**
******************************************************/

inline std::vector<EditorObject*> LevelView::getSpriteList () const { return m_listSprite;};


inline std::string LevelView::getFunction(unsigned int index) const
{
    if(index < m_listFunctionLevel.size())
    {
        m_listFunctionLevel.at(index)->getFunction();
    }
    else
    {
        std::runtime_error("std::string getFunction(unsigned int index) bad index");
    }
}

inline unsigned int LevelView::getNbCurves() const { return m_listFunctionLevel.size();};

/****************************************************
**
******************************************************/

#endif // LEVELVIEW_H
