#include "Player.h"
#include <SFML/Graphics.hpp>
#include <boost/filesystem.hpp>
#include <iostream>


Player::Player(float factor)
	:
	m_name("TestName"),
	m_health(100),
	m_frequency(10),
	m_position({ 22,33 })
{

	boost::filesystem::path fs_path("..\\Link.png");
	
	if (!m_texture.loadFromFile(fs_path.string())) {
		// error...
		std::cerr << "Error loading texture. Either not the right name or missing..." << std::endl;
	}

	m_SubTileAnimationMap.emplace("point_down", SubTile({ Position({31, 7}), Size({ 13, 16 }) }));
	m_SubTileAnimationMap.emplace("point_left", SubTile({ Position({61, 7}), Size({ 13, 16 }) }));
	m_SubTileAnimationMap.emplace("point_up", SubTile({ Position({92, 7}), Size({ 13, 16 }) }));
	m_SubTileAnimationMap.emplace("point_right", SubTile({ Position({121, 7}), Size({ 13, 16 }) }));


	m_SubTileAnimationMap.emplace("walk_down", SubTile({ Position({31, 37}), Size({ 13, 16 }) }));
	m_SubTileAnimationMap.emplace("walk_left", SubTile({ Position({61, 37}), Size({ 13, 16 }) }));
	m_SubTileAnimationMap.emplace("walk_up", SubTile({ Position({92, 37}), Size({ 13, 16 }) }));
	m_SubTileAnimationMap.emplace("walk_right", SubTile({ Position({121, 37}), Size({ 13, 16 }) }));


	// m_SubTileAnimationMap.insert(std::make_pair<std::string, SubTile>("point_left",		{ {2, 3}, { 31, 31 } }));

	m_sprite.setTexture(m_texture);
	SubTile spriteAnim = m_SubTileAnimationMap.at("point_down");
	m_sprite.setTextureRect(
		sf::IntRect(
			spriteAnim.position.m_x, 
			spriteAnim.position.m_y, 
			spriteAnim.size.m_width, 
			spriteAnim.size.m_height
	)); // just use a part of the loaded texture

	m_sprite.scale(sf::Vector2f(factor, factor)); // factor relative to the current scale
	m_sprite.setColor(sf::Color(215, 122, 155)); // change color
	m_sprite.setPosition(m_position.m_x, m_position.m_y);	// set absolute position
}
void Player::setFrequency(int frequency)
{
	m_frequency = frequency;
}

void Player::move(DIRECTION direction, int pixel)
{
	static bool test = false;
	SubTile spriteAnim = m_SubTileAnimationMap.at("point_down");

	switch (direction)
	{
	case DIRECTION::DOWN:
		m_position.m_y += pixel;
		if (test)	spriteAnim = m_SubTileAnimationMap.at("walk_down");
		else		spriteAnim = m_SubTileAnimationMap.at("point_down");
		spriteAnim = m_SubTileAnimationMap.at("point_down");
		break;
	case DIRECTION::LEFT:
		m_position.m_x -= pixel;
		if (test)	spriteAnim = m_SubTileAnimationMap.at("walk_left");
		else		spriteAnim = m_SubTileAnimationMap.at("point_left");
		break;
	case DIRECTION::RIGHT:
		m_position.m_x += pixel;
		if(test)	spriteAnim = m_SubTileAnimationMap.at("walk_right");
		else		spriteAnim = m_SubTileAnimationMap.at("point_right");
		break;
	case DIRECTION::UP:
		m_position.m_y -= pixel;
		if (test)	spriteAnim = m_SubTileAnimationMap.at("walk_up");
		else		spriteAnim = m_SubTileAnimationMap.at("point_up");
		break;
	default:
		break;
	}
	test = !test;

	m_sprite.setTextureRect(
		sf::IntRect(
			spriteAnim.position.m_x,
			spriteAnim.position.m_y,
			spriteAnim.size.m_width,
			spriteAnim.size.m_height
	)); // just use a part of the loaded texture

	m_sprite.setPosition(m_position.m_x, m_position.m_y);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	states.texture = NULL;

	// draw the vertex array
	target.draw(m_sprite, states);
}