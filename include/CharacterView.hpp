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
    	CharacterView(const CharacterModel& model, float scale = 1.0f);
    	/** Default destructor */
    	virtual ~CharacterView();
    	virtual void show();
    	virtual void draw(sf::RenderTarget& target);
        sf::Vector2f getPosition()const;
        sf::FloatRect getRectLocal()const;
        sf::Sound m_sound;
        void setSize(int width, int height);
        void setTexture(const sf::Texture* texture, int frameWidth, int frameHeight);
        sf::FloatRect getGlobalBounds() const;
        bool getDirection() const;
        void setDirection(bool direction);

	protected:
        AniSprite m_animation;
        const CharacterModel& m_model;
        bool m_left;
        float m_scale;
        static sf::SoundBuffer soundBuff;
        static bool soundBufferLoaded;

        static bool loadSoundBuffer(const char* filename = FilenameSoundBuffer);

        bool m_loadedTextureSuccess;
        sf::Texture* m_ArtTexture;
    private:
         CharacterView(const CharacterView& copy);
};

inline sf::FloatRect CharacterView::getRectLocal() const {return m_animation.getLocalBounds();};

inline sf::Vector2f CharacterView::getPosition() const {return m_animation.getPosition();};

inline sf::FloatRect CharacterView::getGlobalBounds() const{ return m_animation.getGlobalBounds();};

inline void CharacterView::setSize(int width, int height)
{
	m_animation.SetFrameSize(width, height);
	m_animation.SetLoopTime(1);
}

inline bool CharacterView::getDirection() const {return m_left;}

inline void CharacterView::setDirection(bool direction) {std::cout << "CharacterView::is_left"<<direction << std::endl; m_left = direction;}

inline void CharacterView::setTexture(const sf::Texture* texture, int frameWidth, int frameHeight)
{
    m_loadedTextureSuccess = (texture != 0);

    if(m_loadedTextureSuccess)
    {
        m_ArtTexture = 0;
        m_animation.setTexture(*texture);
    }
    else
    {
        #ifdef DEBUG
            // // std::cout << "PROBLEME pas charge limage du personnage !" << std::endl;
            // // std::cout << "w : " << frameWidth << " h : " << frameHeight << std::endl;
        #endif
        m_ArtTexture = new sf::Texture;
        m_ArtTexture->create(frameWidth, frameHeight);
        m_animation.setTexture(*m_ArtTexture);
    }

	setSize(frameWidth, frameHeight);
}

#endif // CHARACTERVIEW_HPP
