#ifndef RESOURCESMANAGERSFML2_1_HPP
#define RESOURCESMANAGERSFML2_1_HPP

#ifdef DEBUG
	#include <iostream>
#endif// DEBUG

#include <map>
#include <string>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#define FOR_STL_ITERATOR(container_type, name, iteratorName) for(container_type::iterator iteratorName=name.begin(); iteratorName!=name.end(); iteratorName++)

template<class T>
class ResourcesManagerSFML2_0
{
	typedef std::map<std::string, T*> map_string_ptrT;

	public:
		T* getResource(const std::string& fileName);
	protected:
		ResourcesManagerSFML2_0();
		virtual ~ResourcesManagerSFML2_0();
		std::map<std::string, T*> m_resources;

		virtual void loadFromFile(const std::string& fileName)=0;
};

class TextureManager : public ResourcesManagerSFML2_0<sf::Texture>
{
	typedef std::map<sf::IntRect, sf::Texture*, std::not_equal_to<sf::IntRect> > map_IntRect_ptrTexture;
	typedef std::map<std::string, map_IntRect_ptrTexture > map_string_IntRect_ptrTexture;
	public:
		using ResourcesManagerSFML2_0::getResource;
		sf::Texture* getResource(const std::string& fileName, const sf::IntRect &area);
		static TextureManager* getTextureManager();
	private:
		map_string_IntRect_ptrTexture m_subrectTextures;

		void loadFromFile(const std::string& fileName);
		void loadFromFile(const std::string &fileName, const sf::IntRect &area);
		TextureManager();
		~TextureManager();
};

class FontManager : public ResourcesManagerSFML2_0<sf::Font>
{
	public:
		using ResourcesManagerSFML2_0::getResource;
		static FontManager* getFontManager();
	private:
		void loadFromFile(const std::string& fileName);
		FontManager();
		~FontManager();
};

class SoundBufferManager : public ResourcesManagerSFML2_0<sf::SoundBuffer>
{
	public:
		using ResourcesManagerSFML2_0::getResource;
		static SoundBufferManager* getSoundBufferManager();
	private:
		void loadFromFile(const std::string& fileName);
		SoundBufferManager();
		~SoundBufferManager();
};


/** ********************************************************** ResourcesManagerSFML2_0 ********************************************************** **/

template<class T>
T* ResourcesManagerSFML2_0<T>::getResource(const std::string& fileName)
{
	if(m_resources.find(fileName)==m_resources.end())
		loadFromFile(fileName);

    #ifdef DEBUG
//        if(fileName == "resources/sprites/robot3.png")
        // // std::cout << "THIS ONE used : " << fileName << std::endl;
    #endif

	if(m_resources.find(fileName)!=m_resources.end())
	{
        #ifdef DEBUG
            // // std::cout << "returning m_resources[" << fileName << "]" << std::endl;
        #endif
		return m_resources[fileName];
	}
	else
	{
        #ifdef DEBUG
            // // std::cout << "returning 0" << std::endl;
        #endif
		return 0;
	}
}

template<class T>
ResourcesManagerSFML2_0<T>::ResourcesManagerSFML2_0()
{
}

template<class T>
ResourcesManagerSFML2_0<T>::~ResourcesManagerSFML2_0()
{
	#ifdef DEBUG
		// // std::cout << "destructor ResourcesManagerSFML2_1" << std::endl;
		// // std::cout << "m_resources.size() : " << m_resources.size() << std::endl;
	#endif
	FOR_STL_ITERATOR(typename map_string_ptrT, m_resources, it)
	{
		delete it->second;
		m_resources.erase(it);
		#ifdef DEBUG
			// // std::cout << "m_resources.size()F : " << m_resources.size() << std::endl << std::endl;;
		#endif
	}
}

#endif // RESOURCESMANAGERSFML2_1_HPP
