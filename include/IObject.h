#pragma once

#include <SFML/Graphics.hpp>

class IObject
{
public:
	virtual void update() = 0;
	//virtual void draw(sf::RenderWindow& renderWindow, sf::RenderStates renderStates) const = 0;
	// virtual void collide(const IObject& otherObject) = 0;
};

