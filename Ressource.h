#pragma once

#include<string>
#include<vector>
#include<iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum TextureName
{
	TILESET1 = 0,
	TILESET2,
	DROPHEALTH,
	HERO,
	IMP,
	SPITTER,
	THUG,
	SPIT,
	SWITCH,
	CRATE,
	DUST,
	TITLE,
	CONTROLS,
	GAMEOVER,
	PORTAL1,
	PORTAL2,
	DOOR,
	LIFE,
	LIFE_BACK,
	GLOVE,
	GLOVE_BACK,
	EXIT1,
	EXIT2,
	MYSTERE
};

enum BufferName
{
	TELEPORT = 0,
	SHOT,
	HIT,
	FOOT
};

class Ressource
{
public:
	static Ressource& getInstance()
	{
		static Ressource instance;
		return instance;
	}

	~Ressource();

	int load_image(std::string path);
	int load_wav(std::string path);

	sf::Texture& texture_get(int index);
	const sf::SoundBuffer& buffer_get(int index);

private:
	Ressource()
		: textures()
		, buffers()
	{
		
	}

	Ressource(Ressource const&);
	void operator=(Ressource const&);

private:
	std::vector<sf::Texture> textures;
	std::vector<sf::SoundBuffer*> buffers;
};

