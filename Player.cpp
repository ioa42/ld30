#include "Player.h"
#include "Imp.h"

Player::Player(sf::Texture& t, int x, int y)
	: Entity(t, x, y, 32, 32, true)
	, life(6)
	, max_life(6)
	, glove(3)
	, max_glove(3)
	, item(nullptr)
	, view(sf::FloatRect(0, 0, 480 * 2, 320 * 2))
	, clock()
	, timer(0)
	, acceleration()
{
}

Player::~Player(void)
{
}

void Player::update()
{
	if (clock.getElapsedTime().asMilliseconds() > 117)
		timer++;

	dead = false;
	if (invu)
		invu--;
	if (anim != DEATH)
	{
		move_x = 0;
		move_y = 0;
	}

	float speed = 4;
	const float MAX_SPEED = 4;
	if (anim == IDLE || anim == RUN)
	{
		int xx = move_x;
		int yy = move_y;

		if (sf::Joystick::isConnected(0))
		{
			if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) > 25)
				move_x += speed;
			else if(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) < -25)
				move_x -= speed;

			if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) > 25)
				move_y += speed;
			else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) < -25)
				move_y -= speed;
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				// move left...
				move_x -= speed;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				// move right...
				move_x += speed;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				// up...
				move_y -= speed;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				// down...
				move_y += speed;
			}
		}

		// Glove use
		if (glove > 0 && sf::Joystick::isButtonPressed(0, 0) || (!sf::Joystick::isConnected(0) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
		{
			anim = ATTACK;
			frame_delay = 7;
			frame_id = 0;
			move_x = 0;
			move_y = 0;
		}

		if (xx != move_x || yy != move_y)
		{
			if (timer > 32)
			{
				SoundPlayer::getInstance().play((int)FOOT);
				timer = 0;
			}
		}
	}
}

void Player::hurt(int n)
{
	life-= n;
	SoundPlayer::getInstance().play((int)HIT);
	anim = DEATH;
	frame_id = 0;
	frame_delay = 7;
	invu = 90;
}

void Player::update(std::vector<Entity*> ground, std::vector<Entity*> items)
{
	Entity::update(ground, items);
	if (move_y != 0 || move_x != 0) //POTIONS
	{
		for (Entity* prop : items)
		{
			if (!prop->dead_get() && prop->real_get() == real && dynamic_cast<Prop*>(prop) && box.intersects(prop->box_get()) && dynamic_cast<Prop*>(prop)->lifeGain_get())
			{
				life+=dynamic_cast<Prop*>(prop)->lifeGain_get();
				prop->dead_set(true);
			}
		}
	}

	view.setCenter(location.left + location.width / 2, location.top + location.height / 2);

	if (frame_delay == 6 && frame_id == 4 && anim == ATTACK)//ATTACK
	{
		sf::IntRect area = sf::IntRect(box.left + box.width/2, box.top + box.height/2, (box.width * 4)/3, (box.height * 4)/3);
		area.left -= area.width/2;
		area.top -= area.height/2;
		if (direction == WEST)
			area.left -= + box.width+4;
		if (direction == EAST)
			area.left += + box.width+4;
		if (direction == NORTH)
			area.top -= box.height;
		if (direction == SOUTH)
			area.top += box.height;

		bb = sf::RectangleShape(sf::Vector2f(area.width, area.height));
		bb.setFillColor(sf::Color(0,0,0, 0));
		bb.setOutlineColor(sf::Color(255,0,0, 255));
		bb.setOutlineThickness(2);
		bb.setPosition(sf::Vector2f(area.left, area.top));

		bool touched = false;

		for (Entity* prop : items)
			if (prop != this && prop->real_get() == real && !prop->dead_get() && area.intersects(prop->box_get()) && prop->anim_get() != DEATH && prop->anim_get() != SWITCHING)
			{
				touched = true;
				Prop* statue = dynamic_cast<Prop*>(prop);
				if (statue && statue->link_get() == 1)
					switchWorld();
				else if (statue && statue->link_get() == 2)
				{
					gonna_end = true;
					switchWorld();
				}
				else
					prop->switchWorld();
			}

			if (glove > 0)
				glove -= touched;
	}
	else
		for (Entity* prop : items)
		{
			if (anim != SWITCH && !prop->dead_get() && prop->real_get() == real && prop->anim_get() == ATTACK && !invu && dynamic_cast<Imp*>(prop))//ATTACKED BY IMP
			{
				int x = box.left + box.width/2;
				int y = box.top + box.height/2;
				int x2 = x;
				int y2 = y;

				x2 = prop->box_get().left + prop->box_get().width/2;
				y2 = prop->box_get().top + prop->box_get().height/2;

				move_x = x2 - x;
				move_y = y2 - y;
				int speed = 2;
				int dist = move_x * move_x + move_y * move_y;
				dist  = sqrt(dist);
				if (dist < 70)
				{
					hurt(1);
					move_x = -(3.5f * move_x)/dist;
					move_y = -(3.5f * move_y)/dist;
				}
			}
		}
}

sf::View& Player::view_get()
{
	return view;
}

int Player::life_get()
{
 	return life;
}
int Player::max_life_get()
{
	return max_life;
}
bool Player::end_get()
{
	return end;
}
void Player::end_set(bool s)
{
	end =s;
}

int Player::glove_get()
{
	return glove;
}
int Player::max_glove_get()
{
	return max_glove;
}

void Player::initGlove(int n)
{
	max_glove = n;
	glove = n;
}