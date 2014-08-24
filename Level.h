#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <SFML\Graphics.hpp>

#include "Entity.h"

class Level
{
public:
	Level(std::string fileName, sf::Texture& tileset);
	~Level(void);

	std::vector<std::vector<bool>>& ground_get();
	std::vector<Entity*>& items_get();

	void update();
	void draw(sf::RenderWindow& window);

	void addEntity(Entity* e);

private:
	std::vector<std::vector<bool>> ground;
	std::vector<Entity*> items;
	sf::Texture& tileset;
};

