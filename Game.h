#pragma once

#include "Scene.h"
#include "Ressource.h"
#include "Levels.h"
#include "AllEntities.h"

enum LevelName
{
	LV1 = 0,
	LV2
};

class Game : public Scene
{
public:
	Game(void);
	virtual ~Game(void);
	virtual void transition_in(sf::RenderWindow& window) override;
	virtual void transition_out(sf::RenderWindow& window) override;
	virtual void update(sf::Event& event, sf::RenderWindow& window, SceneName& index) override;
	virtual void draw(sf::RenderWindow& window) override;

private:
	std::vector<Level*> levels;
	Player* player;
	LevelName current;
};
