#pragma once
#include <SFML/Audio.hpp>
#include <map>

class SoundManager
{
private:
	// The buffers
	std::map<std::string, sf::SoundBuffer> m_SoundBuffers;

	// The sounds
	std::map<std::string, sf::Sound> m_Sounds;

public:

	void loadSound(const std::string& name, const std::string &filename);

	//Translate id into ref
	sf::Sound& getRef(const std::string& buffer);

	//Constructor
	SoundManager()
	{
	}
};