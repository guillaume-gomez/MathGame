#ifndef GRAVITYCIRCLE_H
#define GRAVITYCIRCLE_H

#include <SFML/Graphics.hpp>

#include "../files.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"
#include "EditorCircle.hpp"


class GravityCircle : public EditorCircle
{
    public:
        GravityCircle(float radius = 1.0f,float radiusMax=0.0f, bool defOrigin = true, std::string filename = FilenameNormalPointTex);
        virtual ~GravityCircle();
        void grow(float step = 0.1f);
        virtual EditorObject* clone() const;
        virtual std::string save(float scale = GraphScale) const;
    protected:
          std::string m_filename;
          float m_radiusMax;
          sf::Texture& m_texture;

};

#endif // GRAVITYCIRCLE_H
