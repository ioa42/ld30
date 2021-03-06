#pragma once

#include <SFML\Graphics.hpp>

#include <vector>

enum SceneName
{
	MENU = 0,
	LVL,
	GAME,
	ENDSCREEN
};

class Scene
{
public:
	Scene(void);
	virtual ~Scene(void) = 0;
	virtual void transition_in(sf::RenderWindow& window) = 0;
	virtual void transition_out(sf::RenderWindow& window) = 0;
	virtual void update(sf::Event& event, sf::RenderWindow& window, SceneName& index, std::vector<bool>& pressed_keys) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
};

