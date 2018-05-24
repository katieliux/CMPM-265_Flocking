#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "Vehicle.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Flocking");

	sf::Clock clock;
	float deltaTime;

	Vehicle* m_vehicle = new Vehicle();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		deltaTime = clock.restart().asSeconds();


		m_vehicle->Update(&window, deltaTime);

		window.clear();
		window.draw(m_vehicle->shape);
		window.display();
	}

	return 0;
}
