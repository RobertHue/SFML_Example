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



	sf::RenderWindow window(sf::VideoMode(512*factor, 512* factor), "SFML Sprites and Stuff");
	window.setVerticalSyncEnabled(true); // to avoid visual artifacts such as tearing
	// After above call, your application will run at the same frequency as the monitor's refresh rate. 
	// window.setFramerateLimit(60); // force to use max fps

	// create the particle system
	ParticleSystem particles(1000);

	// create a clock to track the elapsed time
	sf::Clock clock;

	Player player(factor);
	player.setFrequency(10);

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;


		while (window.pollEvent(event))
		{

			switch (event.type) // event's members are only valid if they match corresponding the event type
			{
				// "close requested" event: we close the window
				case sf::Event::Closed:
					window.close();
					break;

					// key pressed
				case sf::Event::KeyPressed:
					/*
					std::cout << "the " << event.key.code << " key was pressed" << std::endl;
					std::cout << "control:" << event.key.control << std::endl;
					std::cout << "alt:" << event.key.alt << std::endl;
					std::cout << "shift:" << event.key.shift << std::endl;
					std::cout << "system:" << event.key.system << std::endl;

					if (event.key.code == sf::Keyboard::W)
					{

					}
					if (event.key.code == sf::Keyboard::A)
					{

					}
					if (event.key.code == sf::Keyboard::S)
					{

					}
					if (event.key.code == sf::Keyboard::D)
					{

					}*/
					break;

					// we don't process other types of events
				default:
					break;
			}
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

		player.checkKeyboardInput();
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