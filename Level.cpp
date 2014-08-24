#include "Level.h"

Level::Level(std::string file_name, sf::Texture& tileset)
	: ground()
	, items()
	, tileset(tileset)
	, width(0)
	, height(0)
{
	// Read the xml file @ fileName and create the level from it

	using boost::property_tree::ptree;
	ptree pt;

	try
	{
		std::cout << "Parsing : " << file_name;
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
	BOOST_FOREACH(ptree::value_type &v, pt.get_child("map.layer.data"))
	{	
		tiles.push_back(v.second.get<int>("<xmlattr>.gid"));
	}
	
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			Entity* ent = new Entity(tileset, i * 16, j * 16, 16, 16, false);
			int index = i + j * width;

			int subindex = tiles.at(index);
			std::cout << subindex - 1 << std::endl;
			ent->sprite_get().setTextureRect(sf::IntRect(((subindex - 1) % 9) * 16, ((subindex - 1) / 9) * 16, 16, 16));
			
			ground.push_back(ent);
		}
	}
}

Level::~Level(void)
{
	for(Entity* var : items)
		delete var;
}

void Level::update()
{
	for(Entity* var : items)
		var->update();
	for(Entity* var : items)
		var->update(items);
}

void Level::draw(sf::RenderWindow& window)
{
	for(Entity* var : ground)
		var->draw(window);
	for(Entity* var : items)
		var->draw(window);
}

void Level::addEntity(Entity* e)
{
	items.push_back(e);
}