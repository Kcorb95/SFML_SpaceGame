#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class TextureManager
{
private:
	//Array of textures used
	std::map<std::string, sf::Texture> m_Textures;

public:
	//Add a texture from a file
	void loadTexture(const std::string& name, const std::string &filename);

	//Translate id into ref
	sf::Texture& getRef(const std::string& texture);

	//Constructor
	TextureManager()
	{
	}
};