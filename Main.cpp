#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "VehicleSystem.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Flocking");

	sf::Clock clock;

	sf::Clock m_timer;
	float timer = 1.8f;

	float deltaTime;

	VehicleSystem* m_vs = new VehicleSystem();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		if (timer < 1.0f)
			timer += m_timer.restart().asSeconds();
		else
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_vs->AddVehicle(&window);
				timer = 0;
			}
		}
		deltaTime = clock.restart().asSeconds();

		m_vs->Update(&window, deltaTime);
		m_vs->Render(&window);

	}

	return 0;
}
