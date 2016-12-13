#include <SFML/Graphics.hpp>
#include <map>

#include "SoundManager.h"

void SoundManager::loadSound(const std::string& name, const std::string& filename)
{
	//Load the sound
	sf::Sound sound;
	sf::SoundBuffer soundBuffer;
	soundBuffer.loadFromFile(filename);
	sound.setBuffer(soundBuffer);

	//Add it to the list of sound
	this->m_SoundBuffers[name] = soundBuffer;
	this->m_Sounds[name] = sound;
	return;
}

sf::Sound& SoundManager::getRef(const std::string& sound)
{
	return this->m_Sounds.at(sound);
}