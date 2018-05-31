#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "VehicleSystem.h"
#include "Path.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Flocking");

	sf::Clock clock;

	sf::Clock m_timer;
	float timer = .2f;

	float deltaTime;

	
	VehicleSystem* m_vs = new VehicleSystem(&window);
	Path *m_path = new Path(&window);
	m_vs->GetPath(m_path);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		if (timer < .25f)
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			m_vs->WindToggle();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			m_vs->GravityToggle();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
			m_vs->SeekToggle();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			m_vs->SeparateToggle();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			m_vs->AlignmentToggle();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			m_vs->CohesionToggle();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			m_vs->PathingToggle();

		m_vs->Update(&window, deltaTime);
		window.clear();
		m_vs->Render(&window);
		m_path->Render(&window);
		window.display();
	}

	return 0;
}
