#include <SFML/Graphics.hpp>
#include <map>

#include "TextureManager.h"

void TextureManager::loadTexture(const std::string& name, const std::string& filename)
{
	//Load the Texture
	sf::Texture texture;
	texture.loadFromFile(filename);

	//Add it to the list of textures
	this->m_Textures[name] = texture;
	return;
}

sf::Texture& TextureManager::getRef(const std::string& texture)
{
	return this->m_Textures.at(texture);
}