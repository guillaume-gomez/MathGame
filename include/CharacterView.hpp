#ifndef CHARACTERVIEW_HPP
#define CHARACTERVIEW_HPP

#include <fstream>
#include <string>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "AniSprite.hpp"
#include "CharacterModel.hpp"
#include "../files.hpp"
#include "../libs/ResourcesManagerSFML2_1.hpp"


class CharacterView
{
	public:
	CharacterView(const CharacterModel& model, float scale = 1.0f, int _w = 0, int _h = 0);
	/** Default destructor */
	virtual ~CharacterView();
	void show();
	void draw(sf::RenderTarget& target);
        sf::Vector2f getCoords()const;
        sf::FloatRect getRectLocal()const;
        sf::Sound m_sound;
        void setSize(int width, int height);
        void setTexture(const sf::Texture* texture, int frameWidth, int frameHeight);

	private:
        AniSprite m_animation;
        const CharacterModel& m_model;
        bool m_left;
        float m_scale;
        static sf::SoundBuffer soundBuff;
        static bool soundBufferLoaded;

        static bool loadSoundBuffer(const char* filename = FilenameSoundBuffer);
        
};

inline sf::FloatRect CharacterView::getRectLocal()const{return m_animation.getLocalBounds();};
inline sf::Vector2f CharacterView::getCoords()const{return m_animation.getPosition();};

inline void CharacterView::setSize(int width, int height)
{
	m_animation.SetFrameSize(width, height);
	m_animation.SetLoopTime(1);
}

inline void CharacterView::setTexture(const sf::Texture* texture, int frameWidth, int frameHeight)
{
	m_animation.setTexture(*texture);
	setSize(frameWidth, frameHeight);
}

#endif // CHARACTERVIEW_HPP
