#pragma once

#include <vector>

#include "Entity.h"

class Level
{
public:
	Level(void);
	~Level(void);

	void update();
	void draw();

	void addEntity(Entity* e);

private:
	std::vector<std::vector<bool>> ground;
	std::vector<Entity*> items;
};

