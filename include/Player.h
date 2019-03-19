#pragma once

#include <string>
#include <unordered_map>

#include "IObject.h"
#include "Animation.h"
#include "Controller.h" 

enum class DIRECTION {
	DOWN, LEFT, UP, RIGHT
};

class Player : public sf::Drawable, public sf::Transformable, public IObject
{
public:
	using Position = struct s_Position
	{
		int m_x, m_y;
	};

	using Size = struct s_Size {
		int m_width, m_height;
	};

	using SubTile = struct s_SubTile {
		Position position;
		Size size; 
	};

public:
	Player(float factor);

	void move(DIRECTION direction, int px);

	void setFrequency(int frequency);

	void checkKeyboardInput();

private:

	virtual void update() override;
	virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const override;

private:
	std::string m_name;
	int m_health;
	int m_frequency;
	int m_speed;

	Position m_position;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	std::unordered_map<std::string, SubTile> m_SubTileAnimationMap;

	sf::Clock m_clock;
	Controller controller;
};