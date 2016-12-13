#pragma once
#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <memory>

class SoundManager
{
private:
	// The buffers
	std::map<std::string, sf::SoundBuffer> m_SoundBuffers;

	// The Sounds
	std::map<std::string, sf::Sound> m_Sounds;

	// Which sound should we use next, fire 1, 2 or 3
	int m_NextSound = 1;

public:

	void loadSound(const std::string& name, const std::string &filename);

	//Translate id into ref
	sf::Sound& getRef(const std::string& buffer);

	//Constructor
	SoundManager()
	{
	}
};