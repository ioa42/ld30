#include "Level.h"

Level::Level(std::string file_name, sf::Texture& real_world, sf::Texture& fairy_world)
	: real_ground()
	, fairy_ground()
	, real_items()
	, fairy_items()
	, real_world(real_world)
	, fairy_world(fairy_world)
	, width(0)
	, height(0)
	, in_the_real_world(true)
{
	// Read the xml file @ fileName and create the level from it

	using boost::property_tree::ptree;
	ptree pt;

	try
	{
		read_xml(file_name, pt);
		std::cout << pt.get<std::string>("map.layer.<xmlattr>.name") << std::endl;
	}
	catch (...)
	{
		std::cout << "Error will parsing : " << file_name;
	}

	width = pt.get<int>("map.<xmlattr>.width");
	height = pt.get<int>("map.<xmlattr>.height");

	std::vector<int> tiles;
	std::vector<int> solids;

	BOOST_FOREACH(ptree::value_type &v, pt.get_child("map.layer.data"))
	{
		tiles.push_back(v.second.get<int>("<xmlattr>.gid"));
	}

	BOOST_FOREACH(ptree::value_type &v, pt.get_child("map.solid.data"))
	{
		solids.push_back(v.second.get<int>("<xmlattr>.gid"));
	}

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			Entity* ent = new Prop(real_world, i * 16, j * 16, 16, 16, false);
			int index = i + j * width;

			int subindex = tiles.at(index);
			ent->sprite_get().setTextureRect(sf::IntRect(((subindex - 1) % 9) * 16, ((subindex - 1) / 9) * 16, 16, 16));
			ent->solid_set(solids.at(index));

			real_ground.push_back(ent);
		}
	}
}

Level::~Level(void)
{
	for(Entity* var : real_items)
		delete var;
}

std::vector<Entity*>& Level::ground_real_get()
{
	return real_ground;
}

std::vector<Entity*>& Level::items_real_get()
{
	return real_items;
}

std::vector<Entity*>& Level::ground_fairy_get()
{
	return real_ground;
}

std::vector<Entity*>& Level::items_get()
{
	if (in_the_real_world)
		return real_items;
	else
		return fairy_items;
}

void Level::update()
{
	//while (real_items.size() && real_items.back()->dead_get())
	//	real_items.pop_back();
	//while (fairy_items.size() && fairy_items.back()->dead_get())
	//	fairy_items.pop_back();

	for(Entity* var : in_the_real_world ? real_items : fairy_items)
	{
		if (var->real_get())
		{

		}
	}

	if (in_the_real_world)
	{
		for(Entity* var : real_items)
			var->update();
		for(Entity* var : real_items)
			var->update(real_ground, real_items);
	}
	else
	{
		for(Entity* var : fairy_items)
			var->update();
		for(Entity* var : fairy_items)
			var->update(fairy_ground, fairy_items);
	}
}

void Level::draw(sf::RenderWindow& window)
{
	if (in_the_real_world)
	{
		for(Entity* var : real_ground)
			var->draw(window);

		std::sort(real_items.begin(), real_items.end(), compare);

		for(Entity* var : real_items)
			var->draw(window);
	}
	else
	{
		for(Entity* var : fairy_ground)
			var->draw(window);

		std::sort(fairy_items.begin(), fairy_items.end(), compare);

		for(Entity* var : fairy_items)
			var->draw(window);
	}

}

void Level::addRealEntity(Entity* e)
{
	real_items.push_back(e);
}
void Level::addEntity(Entity* e)
{
	if (in_the_real_world)
		real_items.push_back(e);
	else
		fairy_items.push_back(e);
}

void Level::clearEntity()
{
	real_items.clear();
}

void Level::in_the_real_world_set(bool b)
{
	in_the_real_world = b;
}

bool Level::in_the_real_world_get()
{
	return in_the_real_world;
}