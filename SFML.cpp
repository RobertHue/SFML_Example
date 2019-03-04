#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <boost/filesystem.hpp>

#include "ParticleSystem.h"
#include "TileMap.h"
#include "Player.h"


int main()
{
	float factor = 2.f;
	// define the level with an array of tile indices
	const int level[] =
	{
		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
		0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
		0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
		2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	// create the tilemap from the level definition
	TileMap map;
	if (!map.load("..\\graphics-vertex-array-tilemap-tileset.png", sf::Vector2u(32, 32), level, 16, 16))
		return -1;



	sf::RenderWindow window(sf::VideoMode(512*factor, 512* factor), "My 2d Drawings/Sprites");
	
	// create the particle system
	ParticleSystem particles(1000);

	// create a clock to track the elapsed time
	sf::Clock clock, playerClock;

	Player player(factor);
	player.setFrequency(10);

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//boost::filesystem::path full_path(boost::filesystem::current_path());
		//std::cout << "Current path is : " << full_path << std::endl;


		// position


		// scale
		//sprite.setScale(sf::Vector2f(0.5f, 2.f)); // absolute scale factor
		map.setScale(sf::Vector2f(factor, factor));


		// make the particle system emitter follow the mouse
		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		particles.setEmitter(window.mapPixelToCoords(mouse));

		// update it
		sf::Time elapsedTime = clock.restart();
		particles.update(elapsedTime);

		////////////////
		// clear the window with black color
		window.clear(sf::Color::Black);
		/////////////////////////////////////////////////////////////
		// , sf::IntRect(32, 7, 13, 16)
		// do something with the sprites...

		// inside the main loop, between window.clear() and window.display()
		window.draw(map);
		window.draw(particles);

		sf::Time elapsedTimePlayer = playerClock.getElapsedTime();
		if (elapsedTimePlayer.asSeconds() >= 0.2f) {
			// std::cout << elapsedTimePlayer.asSeconds() << std::endl;
			player.move(DIRECTION::RIGHT, 15);
			playerClock.restart();
		}
		window.draw(player);

		/////////////////////////////////////////////////////////////
		// draw everything here...
		// window.draw(...);
		// end the current frame
		window.display();
		////////////////
	}

    return 0;
}